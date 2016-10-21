/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/19 20:53:08 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ray_trace(t_data *d, t_ray r, float coef, t_RGB *color, int depth)
{
	depth = 0;
	t_list	*curr;
	t_list	*curr2;
	float	t;
	void	*closest;
	int		type;
	t_vec3 n;
	t_light currentLight;
	t_vec3 dist;
	t_ray lightRay;
	float lambert;
	int obscured;
	t_vec3	*temp;

	while (depth < 16 && coef > 0.0)
	{
		t = 30000;
		curr = d->scene->objects;
		closest = NULL;
		type = NONE;
		temp = (t_vec3 *)ft_memalloc(sizeof(t_vec3));
		while (curr)
		{
			if (intersect_shape(&r, curr->content, curr->content_size, &t))
			{
				type = curr->content_size;
				closest = curr->content;
			}
			curr = curr->next;
		}
		if (closest)
		{
			scale_vector(t, &r.dir, temp);
			ft_add_vector(&r.start, temp, &r.start);
			normal_shape(&r, &n, closest, type);
			curr = d->scene->objects;
			while (curr)
			{
				if (curr->content_size == LIGHT)
				{
					obscured = 0;
					currentLight = *(t_light *)curr->content;
					ft_sub_vector(&currentLight.props.pos, &r.start, &dist);
					if (ft_dot_vector(&n, &dist) <= 0.0f)
					{
						curr = curr->next;
						continue ;
					}
					t = sqrtf(ft_dot_vector(&dist, &dist));
					if (t <= 0.0)
					{
						curr = curr->next;
						continue ;
					}
					lightRay.start = r.start;
					normalize_vector(&dist);
					lightRay.dir = dist;
					curr2 = d->scene->objects;
					while (curr2 && !obscured)
					{
						if (intersect_shape(&lightRay, curr2->content, curr2->content_size, &t))
							obscured = 1;
						curr2 = curr2->next;
					}
					if (!obscured)
					{
						lambert = ft_dot_vector(&lightRay.dir, &n) * coef;
						color->r += lambert * currentLight.props.color.r * ((t_sphere *)closest)->props.color.r * currentLight.props.radiance;
						color->g += lambert * currentLight.props.color.g * ((t_sphere *)closest)->props.color.g * currentLight.props.radiance;
						color->b += lambert * currentLight.props.color.b * ((t_sphere *)closest)->props.color.b * currentLight.props.radiance;
					}
				}
				curr = curr->next;
			}
			scale_vector(2.0 * ft_dot_vector(&r.dir, &n), &n, temp);
			ft_sub_vector(&r.dir, temp, &r.dir);
			free(temp);
			coef *= ((t_sphere *)closest)->props.reflect;
			depth++;
		}
		else
			break ;
	}
}

void	draw_screen(t_data *d)
{
	int x;
	int y;
	t_ray r;
	float	global_matrix[4][4];
	t_vec3	point;
	t_RGB color;

	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix, 
		d->scene->cam_rot.x,
		d->scene->cam_rot.y,
		d->scene->cam_rot.z);
	ft_tr_translate(global_matrix,
		d->scene->cam_pos.x,
		d->scene->cam_pos.y,
		d->scene->cam_pos.z);
	y = -1;
	while (++y < d->scene->size.y)
	{
		x = -1;
		while (++x < d->scene->size.x)
		{
			color.r = 0;
			color.g = 0;
			color.b = 0;
			r.start.x = d->scene->cam_pos.x;
			r.start.y = d->scene->cam_pos.y;
			r.start.z = d->scene->cam_pos.z;
			point.x = x - d->scene->size.x / 2;
			point.y = y - d->scene->size.y / 2;
			point.z = d->scene->fov * 10;
			ft_vec_mult_mat(&point, global_matrix, &point);
			r.dir.x = point.x - r.start.x;
			r.dir.y = point.y - r.start.y;
			r.dir.z = point.z - r.start.z;
			normalize_vector(&r.dir);
			ray_trace(d, r, 1.0, &color, 0);
			put_pixel(d, x, y, color);
		}
	}
}

void	draw_reload(t_data *d)
{
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, d->scene->size.x + 100, d->scene->size.y + 100);
	d->pixel_img = mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	draw_screen(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

int		expose_hook(t_data *d)
{
	if (d->img)
		mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	else
		draw_reload(d);
	return (0);
}

void	draw_everything(t_data *d)
{
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->scene->size.x, d->scene->size.y, d->scene->name);
	print_scene_info(d);
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_hook(d->win, 2, 3, key_hook, d);
    mlx_loop(d->mlx);
}
