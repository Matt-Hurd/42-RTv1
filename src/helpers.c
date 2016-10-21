/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 20:32:43 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/20 22:55:29 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_shape(t_ray *r, t_vec3 *n, t_list *s, float t)
{
	if (s->content_size == SPHERE)
		normal_sphere(r, s->content, n, t);
	else if (s->content_size == CYLINDER)
		normal_cylinder(r, s->content, n, t);
	else if (s->content_size == PLANE)
		normal_plane(r, s->content, n, t);
	else
		return ;
}

int 	intersect_shape(t_ray *r, void *s, int type, float *t)
{
	if (type == SPHERE)
		return (intersect_sphere(r, s, t));
	if (type == CYLINDER)
		return (intersect_cylinder(r, s, t));
	if (type == PLANE)
		return (intersect_plane(r, s, t));
	else
		return (0);
}
