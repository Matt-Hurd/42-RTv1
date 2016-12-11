/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 04:07:27 by mhurd             #+#    #+#             */
/*   Updated: 2016/12/10 12:39:19 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_radius(t_list *list, void *obj, int type)
{
	char **buff;
	char *tmp;

	if (ft_strchr(list->content, '='))
	{
		buff = ft_strsplit(list->content, '=');
		tmp = ft_strtrim(buff[0]);
		if (ft_strequ(tmp, "radius"))
		{
			if (type == CONE)
				((t_cone *)obj)->radius = (float)ft_atoi(buff[1]) * M_PI / 180;
			if (type == CYLINDER)
				((t_cylinder *)obj)->radius = (float)ft_atoi(buff[1]);
			if (type == SPHERE)
				((t_sphere *)obj)->radius = (float)ft_atoi(buff[1]);
		}
		free(tmp);
		ft_free_strsplit(list->content, buff, '=');
	}
}
