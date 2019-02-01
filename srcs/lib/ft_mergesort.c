/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:02:58 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/02/01 17:33:59 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*merge_lists(t_list *a, t_list *b, int (*cmp)(void *, void *))
{
	t_list		*merged_list;

	merged_list = NULL;
	if (!a || !b)
		return (!a ? b : a);
	if (cmp(a->data, b->data) <= 0)
	{
		merged_list = a;
		merged_list->next = merge_lists(a->next, b, cmp);
	}
	else
	{
		merged_list = b;
		merged_list->next = merge_lists(a, b->next, cmp);
	}
	return (merged_list);
}

static void		partition(t_list *lst, t_list **front, t_list **back)
{
	t_list		*fast;
	t_list		*slow;

	*front = lst;
	if (!lst || !lst->next)
		*back = NULL;
	else
	{
		slow = lst;
		fast = lst->next;
		while (fast)
		{
			if ((fast = fast->next))
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*back = slow->next;
		slow->next = NULL;
	}
}

void			merge_sort(t_list **lst, int (*cmp)(void *, void *))
{
	t_list		*head;
	t_list		*a;
	t_list		*b;

	if (!lst || !*lst || !(*lst)->next)
		return ;
	head = *lst;
	a = NULL;
	b = NULL;
	partition(head, &a, &b);
	merge_sort(&a, cmp);
	merge_sort(&b, cmp);
	*lst = merge_lists(a, b, cmp);
}
