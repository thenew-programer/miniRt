/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_graphics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:37:30 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 15:39:07 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"

void	*rt_graphics_init(void)
{

	void	*display;

	display = mlx_init();
	return (display);
}

void	rt_graphics_destroy(void *display)
{
	mlx_destroy_display(display);
}
