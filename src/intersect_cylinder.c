/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 21:14:45 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/19 21:30:26 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_cylinder(t_ray *r, t_cylinder *c, t_vec3 *n)
{
	ft_sub_vector(&r->start, &c->props.pos, n);
	normalize_vector(n);
}

int		intersect_cylinder(t_ray *r, t_cylinder *c, float *t)
{
	(void)r;
	(void)c;
	(void)t;
	return (0);
}
