/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 21:14:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/22 21:45:28 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_cylinder(t_ray *r, t_cylinder *cy, t_vec3 *n)
{
	float a;

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
	float	discr;

	scale_vector(dot_vect(&r->dir, &cy->props.rot), &cy->props.rot, &oc);
	sub_vect(&r->dir, &oc, &oc);
	sub_vect(&r->start, &cy->props.pos, &delta);
	scale_vector(dot_vect(&delta, &cy->props.rot), &cy->props.rot, &temp);
	sub_vect(&delta, &temp, &delta);
	a[1] = 2 * dot_vect(&oc, &delta);
	a[2] = dot_vect(&delta, &delta) - SQ(cy->radius);
	discr = a[1] * a[1] - 4 * dot_vect(&oc, &oc) * a[2];
	if (discr == 0)
		a[0] = (-a[1] + sqrtf(discr)) / (2 * dot_vect(&oc, &oc));
	else if (discr > 0)
	{
		a[2] = (-a[1] + sqrtf(discr)) / (2 * dot_vect(&oc, &oc));
		a[1] = (-a[1] - sqrtf(discr)) / (2 * dot_vect(&oc, &oc));
		a[0] = ((MIN(a[2], a[1]) < 0) ? MAX(a[2], a[1]) : MIN(a[2], a[1]));
	}
	if (discr >= 0 && a[0] > 0.01 && *t > a[0])
		*t = a[0];
	return (*t == a[0]);
}
