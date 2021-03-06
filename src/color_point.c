/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 23:43:48 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/11 09:57:16 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	calc_blinn(t_recurse *rec)
{
	t_vec3		half;
	float		blinn_term;
	float		reflect;
	float		gloss;

	reflect = ((t_sphere *)rec->closest->content)->props.reflect;
	gloss = ((t_sphere *)rec->closest->content)->props.gloss;
	sub_vect(&rec->light_ray.dir, &rec->r.dir, &half);
	normalize_vector(&half);
	blinn_term = dot_vect(&half, &rec->n);
	blinn_term = MAX(0, reflect * powf(blinn_term, gloss * 100));
	if (gloss < 0.1)
		blinn_term = 0;
	return (blinn_term);
}

void			color_point(t_recurse *rec)
{
	float	lambert;
	float	blinn;

	rec->lit = 1;
	lambert = dot_vect(&rec->light_ray.dir, &rec->n);
	rec->light += lambert;
	blinn = calc_blinn(rec);
	lambert += blinn;
	lambert *= rec->coef;
	lambert *= rec->light_ray.radiance;
	rec->color.r += lambert * rec->light_ray.color.r *
		((t_sphere *)rec->closest->content)->props.color.r;
	rec->color.g += lambert * rec->light_ray.color.g *
		((t_sphere *)rec->closest->content)->props.color.g;
	rec->color.b += lambert * rec->light_ray.color.b *
		((t_sphere *)rec->closest->content)->props.color.b;
}
