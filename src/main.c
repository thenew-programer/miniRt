/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 22:04:09 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 16:30:07 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics/rt_graphics.h"
#include "arena/arena.h"

int	main(void)
{
	t_arena		arena;
	t_image		image = {
		.img = NULL,
		.width = 500,
		.height = 500,
		.next = NULL
	};
	t_window	window = {
		.window = NULL,
		.display = NULL,
		.title = NULL,
		.height = 500,
		.width = 500,
		.images = NULL
	};
	if (arena_create(&arena, 4096, 8) != ARENA_OK)
		return (1);

	window.display = rt_graphics_init();
	rt_window_create(&window);
	rt_image_create(&window, &image);

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++)
		rt_image_put_pixel(&image, i, j, 0xFF0000 | 0x00FF00 | 0x0000FF);
	}
	rt_window_display_image(&window, &image);
	mlx_loop(window.display);
	// rt_window_run(&window, renderer, t_window);
}
