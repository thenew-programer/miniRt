/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:04:55 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 16:25:02 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_image.h"

int		rt_image_create(t_window *w, t_image *img)
{
	if (!img || !w)
		return (-1);
	img->img = mlx_new_image(w->display, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	return (0);
}

void	rt_image_destroy(t_window *w, t_image *img)
{
	if (!w || !img)
		return ;
	mlx_destroy_image(w->display, img->img);
	img->img = (void *)0;
}

void	rt_image_put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->line_length + x * img->bpp / 8);
		*(unsigned int *)dst = color;
	}
}
