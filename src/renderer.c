/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/22 22:48:56 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ray_trace(t_data *d, t_ray r, float coef, int depth)
{
	t_list	*curr;
	float	t;
	int		type;
	t_vec3	n;
	t_vec3	*temp;

	d->scene->coef = coef;
	while (depth < 1 && d->scene->coef > 0.0)
	{
		t = 30000;
		curr = d->scene->objects;
		d->scene->closest = NULL;
		type = NONE;
		temp = (t_vec3 *)ft_memalloc(sizeof(t_vec3));
		while (curr)
		{
			if (intersect_shape(&r, curr->content, curr->content_size, &t))
				d->scene->closest = curr;
			curr = curr->next;
		}
		if (d->scene->closest)
		{
			scale_vector(t, &r.dir, temp);
			ft_add_vector(&r.start, temp, &r.start);
			normal_shape(&r, &n, d->scene->closest);
			curr = d->scene->objects;
			while (curr)
			{
				if (curr->content_size == LIGHT)
					calc_light(d, curr, r, n);
				curr = curr->next;
			}
			scale_vector(((d->scene->closest->content_size == SPHERE) ? 1 : 2) * dot_vect(&r.dir, &n), &n, temp);
			sub_vect(&r.dir, temp, &r.dir);
			free(temp);
			d->scene->coef *= ((t_sphere *)d->scene->closest->content)->props.reflect;
			depth++;
		}
		else
			break ;
	}
}

void	draw_screen(t_data *d)
{
	int		x;
	int		y;
	t_ray	r;
	float	global_matrix[4][4];
	t_vec3	point;

	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix, d->scene->cam_rot.x, d->scene->cam_rot.y,
		d->scene->cam_rot.z);
	ft_tr_translate(global_matrix, d->scene->cam_pos.x, d->scene->cam_pos.y,
		d->scene->cam_pos.z);
	y = -1;
	while (++y < d->scene->size.y)
	{
		x = -1;
		while (++x < d->scene->size.x)
		{
			clear_color(&d->scene->color);
			scale_vector(1, &d->scene->cam_pos, &r.start);
			point.x = x - d->scene->size.x / 2;
			point.y = y - d->scene->size.y / 2;
			point.z = d->scene->fov * 10;
			ft_vec_mult_mat(&point, global_matrix, &point);
			sub_vect(&point, &r.start, &r.dir);
			normalize_vector(&r.dir);
			ray_trace(d, r, 1.0, 0);
			put_pixel(d, x, y, d->scene->color);
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
