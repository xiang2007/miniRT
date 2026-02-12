/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:27:14 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/04 16:27:16 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*newn;

	if (!lst || !f || !del)
		return (NULL);
	newl = NULL;
	while (lst)
	{
		newn = ft_lstnew(f(lst->content));
		if (!newn)
		{
			ft_lstclear(&newl, del);
			return (NULL);
		}
		ft_lstadd_back(&newl, newn);
		lst = lst->next;
	}
	return (newl);
}
