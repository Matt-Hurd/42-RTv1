/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:26:41 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 23:47:54 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_color(char *color, t_RGB *ref)
{
	char **buff;

	buff = ft_strsplit(color, ',');
	if (ft_count_words(color, ',') != 3)
		ft_error("Config Format Error");
	//write hex detection
	ref->r = (float)ft_atoi(buff[0]) / 255;
	ref->g = (float)ft_atoi(buff[1]) / 255;
	ref->b = (float)ft_atoi(buff[2]) / 255;
}

void	parse_triple(char *triple, t_vec3 *ref)
{
	char **buff;

	buff = ft_strsplit(triple, ',');
	if (ft_count_words(triple, ',') != 3)
		ft_error("Config Format Error");
	//Write atof
	ref->x = ft_atoi(buff[0]);
	ref->y = ft_atoi(buff[1]);
	ref->z = ft_atoi(buff[2]);
}

void	parse_scene(t_data *d, t_list *list)
{
	char **buff;

	if (!d->scene)
		d->scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	while (list && !ft_strchr(list->content, '['))
	{
		if (ft_strchr(list->content, '='))
		{
			buff = ft_strsplit(list->content, '=');
			buff[0] = ft_strtrim(buff[0]);
			buff[1] = ft_strtrim(buff[1]);
			if (ft_strequ(buff[0], "name"))
				d->scene->name = buff[1];
			else if (ft_strequ(buff[0], "width"))
				d->scene->size.x = ft_atoi(buff[1]);
			else if (ft_strequ(buff[0], "height"))
				d->scene->size.y = ft_atoi(buff[1]);
			else if (ft_strequ(buff[0], "fov"))
				d->scene->fov = ft_atoi(buff[1]); //change to atof
			else if (ft_strequ(buff[0], "camera"))
				parse_triple(buff[1], &d->scene->cam_pos);
			else if (ft_strequ(buff[0], "cameraRot"))
				parse_triple(buff[1], &d->scene->cam_rot);
			free(buff);
		}
		list = list->next;
	}
	d->scene->cam_rot.x *= M_PI / 180;
	d->scene->cam_rot.y *= M_PI / 180;
	d->scene->cam_rot.z *= M_PI / 180;
}

void	parse_list(t_data *d, t_list *list)
{
	while (list)
	{
		if (ft_strequ(list->content, "[scene]"))
			parse_scene(d, list->next);
		if (ft_strequ(list->content, "[sphere]"))
			parse_sphere(d, list->next);
		if (ft_strequ(list->content, "[cone]"))
			parse_cone(d, list->next);
		if (ft_strequ(list->content, "[cylinder]"))
			parse_cylinder(d, list->next);
		if (ft_strequ(list->content, "[plane]"))
			parse_plane(d, list->next);
		if (ft_strequ(list->content, "[light]"))
			parse_light(d, list->next);
		if (list)
			list = list->next;
	}
}

void	parse_file(t_data *d, char *filename)
{
	char	*buff;
	int		result;
	int		fd;
	t_list	*list;

	fd = open(filename, O_RDONLY);
	list = NULL;
	while ((result = ft_get_next_line(fd, &buff)) > 0)
		ft_lst_add_back(&list, ft_lstnew(buff, ft_strlen(buff) + 1));
	if (result < 0)
		ft_error_unknown();
	if (!d->scene)
		d->scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	parse_list(d, list);
	close(fd);
}