/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 22:41:35 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/24 10:01:24 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH3D_H
# define MATH3D_H

#include <math.h>
#include "../types/rt_types.h"

t_vec3	vec3(float x, float y, float z);

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);

t_vec3	vec3_mul(t_vec3 v1, t_vec3 v2);

t_vec3	vec3_div(t_vec3 v1, t_vec3 v2);

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);

t_vec3	vec3_scaler_mul(t_vec3 v1, float t);

t_vec3	vec3_scaler_div(t_vec3 v1, float t);

double	vec3_dot(t_vec3 v1, t_vec3 v2);

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);

double	vec3_length_sqrt(t_vec3 v1);

double	vec3_length(t_vec3 v1);

t_vec3	vec3_unit_vector(t_vec3 v);

#endif
