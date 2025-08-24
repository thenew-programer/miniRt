/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_window.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:22:11 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 16:10:35 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RT_WINDOW_H
# define RT_WINDOW_H

# include "rt_graphics_types.h"

int		rt_window_create(t_window *w);
void	rt_window_destroy(t_window *w);

int		rt_window_display_image(t_window *w, const t_image *image);
void	rt_window_set_event_handlers(t_window *w, const t_event_handlers *handlers);

void	rt_window_run(t_window *w, int (*rt_renderer)(void *data), void *user_data);
void	rt_window_stop(t_window *w);

#endif /* RT_WINDOW_H */
