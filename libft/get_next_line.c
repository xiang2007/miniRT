/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:45:57 by ydylan-k          #+#    #+#             */
/*   Updated: 2025/06/11 16:38:08 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		join_line(t_list *list, char **line, t_node *manager);
static void		check_leftovers(t_node *manager);
static void		read_next_line(int fd, t_node *manager);
static size_t	check_line(t_list *node);

char	*get_next_line(int fd)
{
	static t_node	manager;
	char			*line;	

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_next_line(fd, &manager);
	if (!manager.head || !manager.tail)
		return (NULL);
	join_line(manager.head, &line, &manager);
	if (!line)
		return (NULL);
	check_leftovers(&manager);
	return (line);
}

static void	read_next_line(int fd, t_node *manager)
{
	t_list	*new_node;
	t_list	*node;
	ssize_t	read_len;

	node = manager->head;
	while (check_line(node))
	{
		new_node = ft_lstnew(NULL);
		if (!new_node)
			return ;
		new_node->content = malloc(BUFFER_SIZE + 1);
		if (!new_node->content)
			return (ft_lstclear(&manager->head, free));
		read_len = read(fd, new_node->content, BUFFER_SIZE);
		if (read_len == -1 || read_len == 0)
			return (ft_lstdelone(new_node, free));
		new_node->content[read_len] = '\0';
		ft_lstadd_back(new_node, manager);
		node = new_node;
	}
}

static size_t	check_line(t_list *node)
{
	size_t	idx;

	if (!node)
		return (1);
	idx = 0;
	while (node->content[idx])
	{
		if (node->content[idx] == '\n')
		{
			node->length = ++idx;
			return (0);
		}
		idx++;
	}
	node->length = idx;
	return (1);
}

static void	join_line(t_list *list, char **line, t_node *manager)
{
	t_list	*node;
	size_t	total_length;
	size_t	idx;

	node = manager->head;
	total_length = 0;
	while (node)
	{
		total_length += node->length;
		node = node->next;
	}
	if (!total_length)
		return ;
	*line = malloc((total_length + 1) * sizeof(char));
	if (!*line)
		return ;
	total_length = 0;
	while (list && list->content)
	{
		idx = 0;
		while (list->content[idx] && idx < list->length)
			(*line)[total_length++] = list->content[idx++];
		list = list->next;
	}
	(*line)[total_length] = '\0';
}

static void	check_leftovers(t_node *manager)
{
	char	*temp;
	t_list	*new_node;
	size_t	idx;
	size_t	start;

	idx = 0;
	start = manager->tail->length;
	temp = manager->tail->content;
	while (temp[start])
		temp[idx++] = temp[start++];
	temp[idx] = '\0';
	new_node = ft_lstnew(temp);
	if (!new_node)
		return (ft_lstdelone(new_node, free));
	new_node->length = BUFFER_SIZE - manager->tail->length + 1;
	manager->tail->content = NULL;
	manager->tail = NULL;
	ft_lstclear(&manager->head, free);
	if (!*new_node->content)
		return (ft_lstdelone(new_node, free));
	else
	{
		manager->tail = new_node;
		manager->head = new_node;
	}
}
