/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 17:14:06 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/22 01:20:27 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_props(t_list *list, t_props *props)
{
	char		**buff;

	while (list && !ft_strchr(list->content, '['))
	{
		if (ft_strchr(list->content, '='))
		{
			buff = ft_strsplit(list->content, '=');
			buff[0] = ft_strtrim(buff[0]);
			buff[1] = ft_strtrim(buff[1]);
			if (ft_strequ(buff[0], "pos"))
				parse_triple(buff[1], &props->pos);
			else if (ft_strequ(buff[0], "rot"))
				parse_triple(buff[1], &props->rot);
			else if (ft_strequ(buff[0], "color"))
				parse_color(buff[1], &props->color);
			else if (ft_strequ(buff[0], "reflect"))
				props->reflect = (float)ft_atoi(buff[1]) / 100; //change to atof
			else if (ft_strequ(buff[0], "radiance"))
				props->radiance = (float)ft_atoi(buff[1]) / 100; //change to atof
			free(buff);
		}
		list = list->next;
	}
	props->rot.x *= M_PI / 180;
	props->rot.y *= M_PI / 180;
	props->rot.z *= M_PI / 180;
}

void	parse_sphere(t_data *d, t_list *list)
{
	char		**buff;
	t_sphere	*sphere;
	t_list		*ret;

	sphere = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	parse_props(list, &sphere->props);
	if (!d->scene)
		d->scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	while (list && !ft_strchr(list->content, '['))
	{
		if (ft_strchr(list->content, '='))
		{
			buff = ft_strsplit(list->content, '=');
			buff[0] = ft_strtrim(buff[0]);
			if (ft_strequ(buff[0], "radius"))
				sphere->radius = ft_atoi(buff[1]); //change to atof
			free(buff);
		}
		list = list->next;
	}
	ret = ft_lstnew(sphere, sizeof(t_sphere));
	ret->content_size = SPHERE;
	ft_lstadd(&d->scene->objects, ret);
}

void	parse_plane(t_data *d, t_list *list)
{
	t_plane		*plane;
	t_list		*ret;
	float		global_matrix[4][4];
	t_vec3		n;

	n.x = 0;
	n.y = 0;
	n.z = -1;
	ft_make_identity_matrix(global_matrix);
	plane = (t_plane *)ft_memalloc(sizeof(t_plane));
	parse_props(list, &plane->props);
	ft_tr_rotate(global_matrix, 
		plane->props.rot.x,
		plane->props.rot.y,
		plane->props.rot.z);
	ft_vec_mult_mat(&n, global_matrix, &plane->props.rot);
	ret = ft_lstnew(plane, sizeof(t_plane));
	ret->content_size = PLANE;
	ft_lstadd(&d->scene->objects, ret);
}

void	parse_cylinder(t_data *d, t_list *list)
{
	char		**buff;
	t_cylinder	*cylinder;
	t_list		*ret;
	float		global_matrix[4][4];
	t_vec3		n;

	n.x = 0;
	n.y = -1;
	n.z = 0;
	cylinder = (t_cylinder *)ft_memalloc(sizeof(t_cylinder));
	parse_props(list, &cylinder->props);
	while (list && !ft_strchr(list->content, '['))
	{
		if (ft_strchr(list->content, '='))
		{
			buff = ft_strsplit(list->content, '=');
			buff[0] = ft_strtrim(buff[0]);
			if (ft_strequ(buff[0], "radius"))
				cylinder->radius = ft_atoi(buff[1]); //change to atof
			free(buff);
		}
		list = list->next;
	}
	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix, 
		cylinder->props.rot.x,
		cylinder->props.rot.y,
		cylinder->props.rot.z);
	ft_vec_mult_mat(&n, global_matrix, &cylinder->props.rot);
	ret = ft_lstnew(cylinder, sizeof(t_cylinder));
	ret->content_size = CYLINDER;
	ft_lstadd(&d->scene->objects, ret);
}

void	parse_cone(t_data *d, t_list *list)
{
	char		**buff;
	t_cone		*cone;
	t_list		*ret;

	cone = (t_cone *)ft_memalloc(sizeof(t_cone));
	parse_props(list, &cone->props);
	while (list && !ft_strchr(list->content, '['))
	{
		if (ft_strchr(list->content, '='))
		{
			buff = ft_strsplit(list->content, '=');
			buff[0] = ft_strtrim(buff[0]);
			if (ft_strequ(buff[0], "height"))
				cone->height = ft_atoi(buff[1]); //change to atof
			if (ft_strequ(buff[0], "radius"))
				cone->radius = (float)ft_atoi(buff[1]) * M_PI / 180; //change to atof
			free(buff);
		}
		list = list->next;
	}
	ret = ft_lstnew(cone, sizeof(t_cone));
	ret->content_size = CONE;
	ft_lstadd(&d->scene->objects, ret);
}
