#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_FD 65536

typedef struct s_msg
{
	char			*data;
	size_t			len;
	size_t			pos;
	struct s_msg	*next;
}	t_msg;

typedef struct s_client
{
	int		id;
	char	*input;
	size_t	input_len;
	size_t	input_cap;
	t_msg	*out_head;
	t_msg	*out_tail;
}	t_client;

static void	puterr(const char *s)
{
	write(2, s, strlen(s));
}

static int	parse_port(const char *s)
{
	long	n;
	int		i;

	if (!s[0])
		return (-1);
	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		n = n * 10 + s[i] - '0';
		if (n > 65535)
			return (-1);
		i++;
	}
	if (n < 1)
		return (-1);
	return ((int)n);
}

static int	set_nonblocking(int fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0)
		return (0);
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
		return (0);
	return (1);
}

static void	free_messages(t_client *c)
{
	t_msg	*m;
	t_msg	*next;

	m = c->out_head;
	while (m)
	{
		next = m->next;
		free(m->data);
		free(m);
		m = next;
	}
	c->out_head = NULL;
	c->out_tail = NULL;
}

static void	free_client(t_client *c)
{
	if (!c)
		return ;
	free(c->input);
	free_messages(c);
	free(c);
}

static t_msg	*make_message(const char *data, size_t len)
{
	t_msg	*m;

	m = malloc(sizeof(*m));
	if (!m)
		return (NULL);
	m->data = malloc(len);
	if (!m->data)
	{
		free(m);
		return (NULL);
	}
	memcpy(m->data, data, len);
	m->len = len;
	m->pos = 0;
	m->next = NULL;
	return (m);
}

static int	queue_message(t_client *c, const char *data, size_t len)
{
	t_msg	*m;

	m = make_message(data, len);
	if (!m)
		return (0);
	if (c->out_tail)
		c->out_tail->next = m;
	else
		c->out_head = m;
	c->out_tail = m;
	return (1);
}

static int	broadcast(t_client **clients, int sender_fd,
		const char *data, size_t len, int max_fd)
{
	int	fd;

	fd = 0;
	while (fd <= max_fd)
	{
		if (clients[fd] && fd != sender_fd)
		{
			if (!queue_message(clients[fd], data, len))
				return (0);
		}
		fd++;
	}
	return (1);
}

static int	broadcast_status(t_client **clients, int sender_fd,
		int id, const char *status, int max_fd)
{
	char	buf[64];
	int		len;

	len = snprintf(buf, sizeof(buf),
			"relay: peer %d %s\n", id, status);
	return (broadcast(clients, sender_fd, buf, (size_t)len, max_fd));
}

static int	grow_input(t_client *c, size_t extra)
{
	size_t	new_cap;
	char	*tmp;

	if (c->input_len + extra <= c->input_cap)
		return (1);
	new_cap = c->input_cap;
	if (new_cap == 0)
		new_cap = 4096;
	while (new_cap < c->input_len + extra)
	{
		if (new_cap > (size_t)-1 / 2)
			return (0);
		new_cap *= 2;
	}
	tmp = realloc(c->input, new_cap);
	if (!tmp)
		return (0);
	c->input = tmp;
	c->input_cap = new_cap;
	return (1);
}

static int	send_line(t_client **clients, int sender_fd,
		t_client *sender, int max_fd)
{
	char	*msg;
	int		prefix_len;
	size_t	total;

	prefix_len = snprintf(NULL, 0,
			"peer %d says: ", sender->id);
	total = (size_t)prefix_len + sender->input_len + 1;
	msg = malloc(total);
	if (!msg)
		return (0);
	snprintf(msg, (size_t)prefix_len + 1,
		"peer %d says: ", sender->id);
	memcpy(msg + prefix_len, sender->input, sender->input_len);
	msg[total - 1] = '\n';
	if (!broadcast(clients, sender_fd, msg, total, max_fd))
	{
		free(msg);
		return (0);
	}
	free(msg);
	sender->input_len = 0;
	return (1);
}

static int	process_data(t_client **clients, int sender_fd,
		t_client *sender, const char *buf, size_t len, int max_fd)
{
	size_t	i;
	size_t	start;
	size_t	part;

	i = 0;
	start = 0;
	while (i < len)
	{
		if (buf[i] == '\n')
		{
			part = i - start;
			if (!grow_input(sender, part))
				return (0);
			if (part > 0)
				memcpy(sender->input + sender->input_len,
					buf + start, part);
			sender->input_len += part;
			if (!send_line(clients, sender_fd, sender, max_fd))
				return (0);
			start = i + 1;
		}
		i++;
	}
	if (start < len)
	{
		part = len - start;
		if (!grow_input(sender, part))
			return (0);
		memcpy(sender->input + sender->input_len,
			buf + start, part);
		sender->input_len += part;
	}
	return (1);
}

static int	read_client(t_client **clients, int fd,
		t_client *client, int max_fd)
{
	char	buf[8192];
	ssize_t	n;

	while (1)
	{
		n = recv(fd, buf, sizeof(buf), 0);
		if (n > 0)
		{
			if (!process_data(clients, fd, client,
					buf, (size_t)n, max_fd))
				return (0);
		}
		else if (n == 0)
			return (0);
		else if (errno == EINTR)
			continue ;
		else if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (1);
		else
			return (0);
	}
}

static int	flush_client(int fd, t_client *client)
{
	t_msg	*m;
	ssize_t	n;

	while (client->out_head)
	{
		m = client->out_head;
		n = send(fd, m->data + m->pos,
				m->len - m->pos, MSG_NOSIGNAL);
		if (n > 0)
		{
			m->pos += (size_t)n;
			if (m->pos == m->len)
			{
				client->out_head = m->next;
				if (!client->out_head)
					client->out_tail = NULL;
				free(m->data);
				free(m);
			}
		}
		else if (n < 0 && errno == EINTR)
			continue ;
		else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
			return (1);
		else
			return (0);
	}
	return (1);
}

static int	create_server(int port)
{
	struct sockaddr_in	addr;
	int					fd;
	int					opt;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		return (-1);
	opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
			&opt, sizeof(opt)) < 0)
	{
		close(fd);
		return (-1);
	}
	if (!set_nonblocking(fd))
	{
		close(fd);
		return (-1);
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons((unsigned short)port);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		close(fd);
		return (-1);
	}
	if (listen(fd, SOMAXCONN) < 0)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

static void	close_client(t_client **clients, int fd)
{
	if (!clients[fd])
		return ;
	close(fd);
	free_client(clients[fd]);
	clients[fd] = NULL;
}

int	main(int argc, char **argv)
{
	t_client		**clients;
	struct pollfd	*pfds;
	int				server_fd;
	int				port;
	int				next_id;
	int				count;
	int				i;
	int				fd;
	int				max_fd;
	int				nc;
	int				alive;

	signal(SIGPIPE, SIG_IGN);
	if (argc != 2)
	{
		puterr("Invalid argument count\n");
		return (1);
	}
	port = parse_port(argv[1]);
	if (port < 0)
	{
		puterr("Server setup failed\n");
		return (1);
	}
	server_fd = create_server(port);
	if (server_fd < 0)
	{
		puterr("Server setup failed\n");
		return (1);
	}
	clients = calloc(MAX_FD, sizeof(*clients));
	pfds = calloc(MAX_FD + 1, sizeof(*pfds));
	if (!clients || !pfds)
	{
		free(clients);
		free(pfds);
		close(server_fd);
		return (1);
	}
	next_id = 0;
	max_fd = server_fd;
	while (1)
	{
		count = 0;
		pfds[count].fd = server_fd;
		pfds[count].events = POLLIN;
		count++;
		fd = 0;
		while (fd <= max_fd)
		{
			if (fd != server_fd && clients[fd])
			{
				pfds[count].fd = fd;
				pfds[count].events = POLLIN;
				if (clients[fd]->out_head)
					pfds[count].events |= POLLOUT;
				count++;
			}
			fd++;
		}
		if (poll(pfds, (nfds_t)count, -1) < 0)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (pfds[0].revents & POLLIN)
		{
			while (1)
			{
				nc = accept(server_fd, NULL, NULL);
				if (nc < 0)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
						break ;
					break ;
				}
				if (nc >= MAX_FD || !set_nonblocking(nc))
				{
					close(nc);
					continue ;
				}
				clients[nc] = calloc(1, sizeof(*clients[nc]));
				if (!clients[nc])
				{
					close(nc);
					continue ;
				}
				clients[nc]->id = next_id++;
				if (!broadcast_status(clients, nc,
						clients[nc]->id, "joined", max_fd))
				{
					close_client(clients, nc);
					continue ;
				}
				if (nc > max_fd)
					max_fd = nc;
			}
		}
		i = 1;
		while (i < count)
		{
			fd = pfds[i].fd;
			if (!clients[fd])
			{
				i++;
				continue ;
			}
			alive = 1;
			if (pfds[i].revents & POLLIN)
			{
				if (!read_client(clients, fd,
						clients[fd], max_fd))
				{
					broadcast_status(clients, fd,
						clients[fd]->id, "left", max_fd);
					close_client(clients, fd);
					alive = 0;
				}
			}
			if (alive && (pfds[i].revents
					& (POLLERR | POLLHUP | POLLNVAL)))
			{
				broadcast_status(clients, fd,
					clients[fd]->id, "left", max_fd);
				close_client(clients, fd);
				alive = 0;
			}
			if (alive && (pfds[i].revents & POLLOUT))
			{
				if (!flush_client(fd, clients[fd]))
				{
					broadcast_status(clients, fd,
						clients[fd]->id, "left", max_fd);
					close_client(clients, fd);
				}
			}
			i++;
		}
		free(pfds);
		pfds = calloc(MAX_FD + 1, sizeof(*pfds));
		if (!pfds)
			break ;
	}
	fd = 0;
	while (fd <= max_fd)
	{
		if (clients[fd])
			close_client(clients, fd);
		fd++;
	}
	free(clients);
	free(pfds);
	close(server_fd);
	return (1);
}
