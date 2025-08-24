/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_image.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:22:57 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 16:25:38 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_IMAGE_H
# define RT_IMAGE_H

# include "rt_graphics_types.h"

int		rt_image_create(t_window *w, t_image *img);

void	rt_image_destroy(t_window *w, t_image *img);

void	rt_image_put_pixel(t_image *img, int x, int y, int color);

#endif /* RT_IMAGE_H */
