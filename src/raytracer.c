/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 22:42:52 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/22 22:48:02 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	calc_light(t_data *d, t_list *curr, t_ray r, t_vec3 n)
{
	int		obscured;
	t_vec3	dist;
	float	t;
	t_list	*curr2;

	obscured = 0;
	d->scene->currentLight = *(t_light *)curr->content;
	sub_vect(&d->scene->currentLight.props.pos, &r.start, &dist);
	t = sqrtf(dot_vect(&dist, &dist));
	if (!(dot_vect(&n, &dist) <= 0.0f || t <= 0.0))
	{
		d->scene->lightRay.start = r.start;
		normalize_vector(&dist);
		d->scene->lightRay.dir = dist;
		curr2 = d->scene->objects;
		while (curr2 && !obscured)
		{
			if (intersect_shape(&d->scene->lightRay,
				curr2->content, curr2->content_size, &t))
				obscured = 1;
			curr2 = curr2->next;
		}
		if (!obscured)
			color_point(d, n, &d->scene->color, d->scene->coef);
	}
}

void	color_point(t_data *d, t_vec3 n, t_RGB *color, float coef)
{
	float lambert;
	float gloss;

	lambert = dot_vect(&d->scene->lightRay.dir, &n) * coef;
	gloss = ((t_sphere *)d->scene->closest->content)->props.reflect > 0
		? dot_vect(&d->scene->lightRay.dir, &n) : 0;
	gloss = gloss > 0.95 ? (gloss - 0.95) * 10 : 0;
	color->r += gloss;
	color->g += gloss;
	color->b += gloss;
	color->r += lambert * d->scene->currentLight.props.color.r *
		((t_sphere *)d->scene->closest->content)->props.color.r *
		d->scene->currentLight.props.radiance;
	color->g += lambert * d->scene->currentLight.props.color.g *
		((t_sphere *)d->scene->closest->content)->props.color.g *
		d->scene->currentLight.props.radiance;
	color->b += lambert * d->scene->currentLight.props.color.b *
		((t_sphere *)d->scene->closest->content)->props.color.b *
		d->scene->currentLight.props.radiance;
}
