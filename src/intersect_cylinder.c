/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 21:14:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/22 00:53:23 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_cylinder(t_ray *r, t_cylinder *cy, t_vec3 *n, float t)
{
	float a;

	(void)t;
	a = (-cy->props.rot.x * cy->props.pos.x - cy->props.rot.y * cy->props.pos.y
		- cy->props.rot.z * cy->props.pos.z + r->start.x * cy->props.rot.x +
		r->start.y * cy->props.rot.y + r->start.z * cy->props.rot.z) /
		(powf(cy->props.rot.x, 2) + powf(cy->props.rot.y, 2) +
		powf(cy->props.rot.z, 2));
	n->x = (r->start.x - (cy->props.pos.x + cy->props.rot.x * a));
	n->y = (r->start.y - (cy->props.pos.y + cy->props.rot.y * a));
	n->z = (r->start.z - (cy->props.pos.z + cy->props.rot.z * a));
	normalize_vector(n);
}

int		intersect_cylinder(t_ray *r, t_cylinder *cy, float *t)
{
	t_vec3	oc;
	t_vec3	delta;
	t_vec3	temp;
	float	a[3];
	float	b[3];
	float	discr;

	a[0] = ft_dot_vector(&r->dir, &cy->props.rot);
	scale_vector(a[0], &cy->props.rot, &oc);
	ft_sub_vector(&r->dir, &oc, &oc);
	a[0] = ft_dot_vector(&oc, &oc);
	ft_sub_vector(&r->start, &cy->props.pos, &delta);
	scale_vector(ft_dot_vector(&delta, &cy->props.rot), &cy->props.rot, &temp);
	ft_sub_vector(&delta, &temp, &delta);
	a[1] = 2 * ft_dot_vector(&oc, &delta);
	a[2] = ft_dot_vector(&delta, &delta) - SQ(cy->radius);
	discr = a[1] * a[1] - 4 * a[0] * a[2];
	if (discr == 0)
		b[2] = (-a[1] + sqrtf(discr)) / (2 * a[0]);
	else if (discr > 0)
	{
		b[0] = (-a[1] + sqrtf(discr)) / (2 * a[0]);
		b[1] = (-a[1] - sqrtf(discr)) / (2 * a[0]);
		b[2] = (b[0] < b[1] ? b[0] : b[1]);
		b[2] = (b[2] < 0 ? b[1] : b[2]);
	}
	if (b[2] > 0.01 && *t > b[2])
		*t = b[2];
	return (*t == b[2]);
}
