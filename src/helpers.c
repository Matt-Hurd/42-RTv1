/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 20:32:43 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/19 21:24:53 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_shape(t_ray *r, t_vec3 *n, void *s, int type)
{
	if (type == SPHERE)
		normal_sphere(r, s, n);
	else
		return ;
}

int 	intersect_shape(t_ray *r, void *s, int type, float *t)
{
	if (type == SPHERE)
		return (intersect_sphere(r, s, t));
	if (type == CYLINDER)
		return (intersect_cylinder(r, s, t));
	else
		return (0);
}
