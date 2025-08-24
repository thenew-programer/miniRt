/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:25:15 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 09:25:20 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math3d.h"
#include <math.h>

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vec3	vec3_mul(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vec3	vec3_div(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x / v2.x;
	v.y = v1.y / v2.y;
	v.z = v1.z / v2.z;
	return (v);
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vec3 vec3_scaler_mul(t_vec3 v, float t)
{
	t_vec3 res;

	res.x = v.x * t;
	res.y = v.y * t;
	res.z = v.z * t;
	return (res);
}

t_vec3 vec3_scaler_div(t_vec3 v, float t)
{
	t_vec3 res;

	res.x = v.x / t;
	res.y = v.y / t;
	res.z = v.z / t;
	return (res);
}

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	double dot;

	dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (dot);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3 cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}

double	vec3_length_sqrt(t_vec3 v)
{
	double len_sqrt;

	len_sqrt = v.x * v.x + v.y * v.y + v.z * v.z;
	return (len_sqrt);
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_sqrt(v)));
}

t_vec3	vec3_unit_vector(t_vec3 v)
{
	double	len;

	len = vec3_length(v);
	return (vec3_scaler_div(v, len));
}

t_vec3	vec3(float x, float y, float z)
{
	return ((t_vec3){.x=x, .y=y, .z=z});
}
