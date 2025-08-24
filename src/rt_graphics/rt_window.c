/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:39:38 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 16:14:55 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_window.h"

#define ON_EXPOSE	12
#define	ON_DESTROY	17
#define ON_KEYDOWN	2
#define ON_KEYUP	3

int	rt_window_create(t_window *w)
{
	if (!w)
		return (-1);
	w->window = mlx_new_window(w->display, w->width, w->height, w->title);
	if (!w->window)
		return (-1);
	return (0);
}

void	rt_window_destroy(t_window *w)
{
	if (!w || !w->window)
		return ;
	mlx_destroy_window(w->display, w->window);
}

int	rt_window_display_image(t_window *window, const t_image *image)
{
	if (!window || !image)
		return (-1);
	mlx_put_image_to_window(window->display, window->window, image->img, 0, 0);
	return (0);
}

void	rt_window_set_event_handlers(t_window *w, const t_event_handlers *handlers)
{
	if (handlers->on_expose)
		mlx_hook(w->window, ON_EXPOSE, (1L << 15), handlers->on_expose, handlers->user_data);
	if (handlers->on_destroy)
		mlx_hook(w->window, ON_DESTROY, 0, handlers->on_destroy, handlers->user_data);
	if (handlers->on_key_press)
		mlx_hook(w->window, ON_KEYDOWN, 1L, handlers->on_key_press, handlers->user_data);
	if (handlers->on_key_release)
		mlx_hook(w->window, ON_KEYUP, (1L << 1), handlers->on_key_release, handlers->user_data);
}

void	rt_window_run(t_window *w, int (*rt_renderer)(void *data), void *user_data)
{
	mlx_loop_hook(w->display, rt_renderer, user_data);
}

void	rt_window_stop(t_window *w)
{
	mlx_loop_end(w->display);
}
