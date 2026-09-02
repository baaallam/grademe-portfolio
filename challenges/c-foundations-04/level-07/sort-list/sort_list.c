#include "list.h"

ListNode	*sort_list(ListNode *lst, int (*cmp)(int, int))
{
	ListNode	*cur;
	ListNode	*next;
	int			tmp;

	cur = lst;
	while (cur)
	{
		next = cur->next;
		while (next)
		{
			if (!cmp(cur->data, next->data))
			{
				tmp = cur->data;
				cur->data = next->data;
				next->data = tmp;
			}
			next = next->next;
		}
		cur = cur->next;
	}
	return (lst);
}
