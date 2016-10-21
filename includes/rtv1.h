/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:06:16 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/19 21:24:12 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "mlx.h"
# include "libft.h"
# include "libgfx.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>


/*
** KEYS
*/

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78

# define KEY_ROT_X_U 86
# define KEY_ROT_X_D 83
# define KEY_ROT_Y_U 87
# define KEY_ROT_Y_D 84
# define KEY_ROT_Z_U 88
# define KEY_ROT_Z_D 85


void		parse_file(t_data *d, char *filename);
void		draw_everything(t_data *d);
int			key_hook(int keycode, t_data *d);
void		draw_reload(t_data *d);
void		ft_exit(void);
void		ft_error(char *s);
void		ft_error_unknown(void);
void		parse_triple(char *triple, t_vec3 *ref);
void		parse_sphere(t_data *d, t_list *list);
void		parse_color(char *color, t_RGB *ref);
void		parse_cone(t_data *d, t_list *list);
void		parse_cylinder(t_data *d, t_list *list);
void		parse_plane(t_data *d, t_list *list);
void		parse_props(t_list *list, t_props *props);
void		parse_light(t_data *d, t_list *list);
int			intersect_sphere(t_ray *r, t_sphere *s, float *t);
void		normalize_vector(t_vec3 *v);
int 		intersect_shape(t_ray *r, void *s, int type, float *t);
void		normal_shape(t_ray *r, t_vec3 *n, void *s, int type);
void		normal_sphere(t_ray *r, t_sphere *s, t_vec3 *n);
int			intersect_cylinder(t_ray *r, t_cylinder *c, float *t);

//Debugging
void	print_scene_info(t_data *d);
void	print_RGB(t_RGB rgb);

#endif