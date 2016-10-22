/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 21:14:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/22 01:20:09 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_cone(t_ray *r, t_cone *c, t_vec3 *n, float t)
{
	float a;

	(void)t;
	a = (-cy->props.rot.x * cy->props.pos.x - cy->props.rot.y * cy->props.pos.y - cy->props.rot.z * cy->props.pos.z +
		r->start.x * cy->props.rot.x + r->start.y * cy->props.rot.y + r->start.z * cy->props.rot.z) /
		(powf(cy->props.rot.x, 2) + powf(cy->props.rot.y, 2) + powf(cy->props.rot.z, 2));
	n->x = (r->start.x - (cy->props.pos.x + cy->props.rot.x * a));
	n->y = (r->start.y - (cy->props.pos.y + cy->props.rot.y * a));
	n->z = (r->start.z - (cy->props.pos.z + cy->props.rot.z * a));
	normalize_vector(n);
}

int		intersect_ccone(t_ray *r, t_cone *c, float *t)
{
	t_vec3	oc;
	t_vec3	delta;
	t_vec3	temp;
	float	a[3];
	float	b[3];
	float	discr;

	scale_vector(ft_dot_vector(&r->dir, &c->props.rot), &c->props.rot, &temp);
	ft_sub_vector(&r->dir, &temp, &temp);
	a[0] = SQ(cos(r->radius)) * ft_dot_vector(&temp, &temp) - SQ(sin(r->radius)) * SQ(ft_dot_vector(&r->dir, c->props.rot));
	ft_sub_vector(&r->start, &c->props.pos, &delta);
	
}
