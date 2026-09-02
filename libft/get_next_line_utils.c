/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:19:55 by ydylan-k          #+#    #+#             */
/*   Updated: 2025/06/11 16:51:38 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstadd_back(t_list *new, t_node *manager)
{
	t_list	*node;
	
	if (!manager || !new)
		return ;
	if (!manager->head)
	{
		manager->head = new;
		manager->tail = new;
	}
	else
	{
		node = manager->tail;
		node->next = new;
		manager->tail = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->length = 0;
	lst->next = NULL;
	return (lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		tmp = node;
		node = node->next;
		del(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
