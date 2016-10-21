/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 20:57:34 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/21 00:20:52 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_plane(t_ray *r, t_plane *p, t_vec3 *n, float t)
{
	(void)t;
	*n = p->props.rot;
	if (ft_dot_vector(&r->dir, &p->props.rot) > 0)
		scale_vector(-1, n, n);
	normalize_vector(n);
}

int		intersect_plane(t_ray *r, t_plane *p, float *t)
{
	float		n;
	float		d;
	float		res;
	t_vec3		temp;

	ft_sub_vector(&p->props.pos, &r->start, &temp);
	n = ft_dot_vector(&p->props.rot, &temp);
	d = ft_dot_vector(&p->props.rot, &r->dir);
	if ((res = n / d) > 0.01 && res < *t)
		*t = res;
	return ((res == *t) ? 1 : 0);
}
