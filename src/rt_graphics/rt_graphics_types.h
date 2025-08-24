/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_graphics_types.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:09:13 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 16:14:19 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GRAPHICS_TYPES
# define RT_GRAPHICS_TYPES

# include "../../minilibx-linux/mlx.h"

typedef struct s_image
{
	char			*addr;
	void			*img;
	int				bpp;
	int				line_length;
	int				endian;
	int				height;
	int				width;
	struct s_image	*next;
}	t_image;


typedef struct s_window
{
	void	*display;
	void	*window;
	t_image	*images;
	int		height;
	int		width;
	char	*title;
}	t_window;


typedef enum e_key_event
{
	KEY_ESCAPE = 53,
	KEY_Q = 12
}	t_key_event;

typedef struct s_event_handlers
{
	int	(*on_key_press)(int keycode, void *param);
	int	(*on_key_release)(int keycode, void *param);
	int	(*on_destroy)(void *param);
	int	(*on_expose)(void *param);
	int	*user_data;
}	t_event_handlers;

#endif /* RT_GRAPHICS_TYPES */
