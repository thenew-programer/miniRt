/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:30:38 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 09:31:40 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES
# define RT_TYPES

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef t_vec3	t_point3;

typedef t_vec3	t_color;
#endif /* RT_TYPES */
