/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:24:18 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/10 15:52:14 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_dis	*discriminant(t_ray *r, t_sphere *sp)
{
	t_dis	*dis;

	if (!r || !sp)
		return (NULL);
	dis = malloc(sizeof(t_dis));
	if (!dis)
		return (NULL);
	dis->sphere_to_ray = subtract_tuple(r->point, sp->point);
	dis->a = dot_product(r->direction, r->direction);
	dis->b = 2 * (dot_product(r->direction, dis->sphere_to_ray));
	dis->c = dot_product(dis->sphere_to_ray, dis->sphere_to_ray) - 1;
	dis->res = sq(dis->b) - 4 * dis->a * dis->c;
	return (dis);
}

void	free_disct(t_dis *d)
{
	free(d->sphere_to_ray);
	free(d);
}

t_intersect	*create_intersect(double t1, double t2)
{
	t_intersect	*res;

	res = malloc(sizeof(t_intersect));
	if (!res)
		return (NULL);
	res->intersect_count = 2;
	res->intersects = malloc(sizeof(double) * 2);
	res->intersects[0] = t1;
	res->intersects[1] = t2;
	res->next = NULL;
	return (res);
}

void	free_intersect(t_intersect *i)
{
	if (!i)
		return ;
	free(i->intersects);
	free(i);
}

t_intersect	*intersect(t_ray *r, t_sphere *sp)
{
	double		t1;
	double		t2;
	t_dis		*dis;
	t_intersect	*i;

	if (!r || !sp)
		return (NULL);
	dis = discriminant(r, sp);
	if (dis->res < 0)
		return (free_disct(dis), NULL);
	t1 = ((-(dis->b) - sqrt(dis->res)) / (2 * dis->a));
	t2 = ((-(dis->b) + sqrt(dis->res)) / (2 * dis->a));
	i = create_intersect(t1, t2);
	free_disct(dis);
	return (i);
}
