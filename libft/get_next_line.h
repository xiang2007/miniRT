/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:20:07 by ydylan-k          #+#    #+#             */
/*   Updated: 2025/06/11 14:50:38 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	size_t			length;
	struct s_list	*next;
}	t_list;

typedef struct s_node
{
	t_list	*head;
	t_list	*tail;
}	t_node;

char	*get_next_line(int fd);

void	ft_lstadd_back(t_list *new, t_node *manager);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));

t_list	*ft_lstnew(void *content);

#endif