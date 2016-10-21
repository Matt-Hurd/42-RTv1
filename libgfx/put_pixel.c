/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 19:28:29 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/19 16:00:03 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

void	put_pixel(t_data *d, int x, int y, t_RGB color)
{
	int i;

	i = (x * 4) + (y * d->s_line);
	d->pixel_img[i] = MIN(255, color.b * 255);
	d->pixel_img[++i] = MIN(255, color.g * 255);
	d->pixel_img[++i] = MIN(255, color.r * 255);
}
