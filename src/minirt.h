/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:31:29 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 14:29:29 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "arena/arena.h"
# include "rt_scene/rt_scene.h"
# include "rt_graphics/rt_window.h"
# include "rt_graphics/rt_window.h"

typedef struct s_app
{
	t_arena		*arena;
	t_scene		*scene;
	t_window	*screen;
}	t_app;

#endif /* MINIRT_H */
