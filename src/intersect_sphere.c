/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 20:39:50 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/21 00:07:25 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_sphere(t_ray *r, t_sphere *s, t_vec3 *n, float t)
{
	(void)t;
	ft_sub_vector(&r->start, &s->props.pos, n);
	normalize_vector(n);
}

int		intersect_sphere(t_ray *r, t_sphere *s, float *t)
{
	int		retval;
	t_vec3	*dist;
	t_vec3	temp;
	float	discr;

	retval = 0;
	temp.x = ft_dot_vector(&r->dir, &r->dir);
	dist = (t_vec3 *)ft_memalloc(sizeof(t_vec3));
	ft_sub_vector(&r->start, &s->props.pos, dist);
	temp.y = 2 * ft_dot_vector(&r->dir, dist);
	temp.z = ft_dot_vector(dist, dist) - (s->radius * s->radius);
	free(dist);
	discr = temp.y * temp.y - 4 * temp.x * temp.z;
	if(discr < 0)
		return (0);
	temp.x = sqrtf(discr);
	temp.z = (-temp.y - temp.x) / 2;
	temp.y = (-temp.y + temp.x) / 2;
	if(temp.y > temp.z)
		temp.y = temp.z;
	if((temp.y > 0.001f) && (temp.y < *t))
		*t = temp.y;
	return ((*t == temp.y) ? 1 : 0);
}
