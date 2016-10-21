/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 21:14:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/20 22:52:44 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_cylinder(t_ray *r, t_cylinder *c, t_vec3 *n, float t)
{
	(void)t;
	ft_sub_vector(&r->start, &c->props.pos, n);
	normalize_vector(n);
}

int			resolve_quadratic(float det, float a, float b, float *t)
{
	float		sqr;
	float		t_array[2];
	int			ret_value;

	ret_value = 0;
	sqr = sqrt(det);
	t_array[0] = (-b - sqr) / (2 * a);
	t_array[1] = (-b + sqr) / (2 * a);
	if (t_array[0] > 0.1f && (t_array[0] < *t))
	{
		*t = t_array[0];
		ret_value = 1;
	}
	if (t_array[1] > 0.1f && (t_array[1] < *t))
	{
		*t = t_array[1];
		ret_value = 1;
	}
	return (ret_value);
}

int		intersect_cylinder(t_ray *r, t_cylinder *cy, float *t)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	h;

	ft_sub_vector(&r->start, &cy->props.pos, &oc);
	a = SQ(r->dir.x) + SQ(r->dir.z);
	b = (r->dir.x * oc.x + r->dir.z * oc.z);
	c = SQ(oc.x) + SQ(oc.z) - SQ(cy->radius);
	h = SQ(b) - a * c;
	if (h < 0.0001)
		return (0);
	*t = (-b - sqrtf(h)) / a;
	return (1);
}
