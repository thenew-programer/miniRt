/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:57:31 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 10:18:21 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE
# define RT_SCENE

#include "../math3d/math3d.h"
#include "../types/rt_types.h"
#include "../arena/arena.h"

typedef struct s_scene		t_scene;

typedef struct s_material
{
	t_color	color;
}t_material;

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_CYLANDER,
	OBJ_PLANE
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	t_material		material;
	union
	{
		struct
		{
			t_point3	center;
			float		diameter;
		}s_sphere;

		struct
		{
			t_point3	center;
			t_vec3		normal;
			float		diameter;
			float		height;
		}s_cylander;

		struct
		{
			t_point3	point;
			t_vec3		normal;
		}s_plane;

	}u_data;
}	t_object;

typedef struct s_ambient_light
{
	float	ratio;
	t_color	color;
}	t_ambient_light;

typedef struct s_camera
{
	t_point3	center;
	t_vec3		orientation;
	float		fov;
}	t_camera;

typedef struct s_light
{
	t_point3		position;
	float			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

struct s_scene
{
	t_camera		camera;
	t_ambient_light	ambient_light;
	t_light			*lights;
	t_object		*objects;
};

#endif /* RT_SCENE */
