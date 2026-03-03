/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 23:01:44 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 16:37:33 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersect	*intersection(t_d t, t_sp *s)
{
	t_intersect	*i;

	i = malloc(sizeof(t_intersect));
	if (!i)
		return (NULL);
	ft_memset(i, 0, sizeof(t_intersect));
	i->t = t;
	i->object = s;
	i->next = NULL;
	return (i);
}

void	add_intersect(t_intersect *src, t_intersect **dest)
{
	t_intersect	*tail;

	if (!src || !dest)
		return ;
	if (!*dest)
	{
		*dest = src;
		return ;
	}
	tail = *dest;
	while (tail->next)
		tail = tail->next;
	tail->next = src;
}

t_intersect	*intersect(t_sp *s, t_ray *ray)
{
	t_d			a;
	t_d			b;
	t_d			c;
	t_d			d;
	t_tuple		*str;
	t_intersect	*i1;
	t_intersect	*i2;
	t_ray		*l_ray;
	t_matrix	*inv;

	inv = inverse_matrix(s->transform);
	l_ray = transform_ray(ray, inv);
	free_matrix(inv);
	str = sub_free_s2(l_ray->origin, create_point(0, 0, 0));
	a = dot_product(l_ray->direction, l_ray->direction);
	b = 2 * (dot_product(l_ray->direction, str));
	c = dot_product(str, str) - 1;
	d = sq(b) - (4 * a * c);
	free(str);
	if (d < 0)
		return (free_ray(l_ray), NULL);
	i1 = intersection(((-b) - sqrt(d)) / (2 * a), s);
	i2 = intersection(((-b) + sqrt(d)) / (2 * a), s);
	i1->next = i2;
	return (free_ray(l_ray), i1);
}

t_intersect	*hit(t_intersect *it)
{
	t_intersect	*head;
	t_intersect	*best;

	head = it;
	best = NULL;
	while (head)
	{
		if (head->t > 0 && (!best || head->t < best->t))
			best = head;
		head = head->next;
	}
	return (best);
}

void	print_intersect(t_intersect *t)
{
	t_intersect	*tail;

	tail = t;
	while (tail)
	{
		printf("t: %f\n", tail->t);
		tail = tail->next;
	}
}
