/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_graphics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:21:45 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 16:14:28 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GRAPHICS_H
# define RT_GRAPHICS_H

# include "rt_graphics_types.h"
# include "rt_window.h"
# include "rt_image.h"


void	*rt_graphics_init(void);

void	rt_graphics_destroy(void *display);

#endif /* RT_GRAPHICS_H */
