/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:54:43 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/17 12:51:51 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_arena_error	arena_init(
					t_arena *arena,
					void *base,
					size_t size,
					size_t alignment)
{
	if (!arena || !base)
		return (ARENA_ERROR_NULL_PARAM);
	arena->buffer = base;
	arena->size = size;
	arena->offset = 0;
	if (alignment < ARENA_DEFAULT_ALIGNMENT || alignment == 0)
		alignment = ARENA_DEFAULT_ALIGNMENT;
	arena->alignment = alignment;
	arena->own_buffer = false;
	arena->magic = ARENA_MAGIC_NUMBER;
	return (ARENA_OK);
}

t_arena_error	arena_create(
					t_arena *arena,
					size_t	size,
					size_t alignment)
{
	if (!arena)
		return (ARENA_ERROR_NULL_PARAM);
	arena->buffer = malloc(sizeof(char) * size);
	if (!arena->buffer)
		return (ARENA_ERROR_OUT_OF_MEMORY);
	arena->size = size;
	arena->offset = 0;
	if (alignment < ARENA_DEFAULT_ALIGNMENT || alignment == 0)
		alignment = ARENA_DEFAULT_ALIGNMENT;
	arena->alignment = alignment;
	arena->own_buffer = true;
	arena->magic = ARENA_MAGIC_NUMBER;
	return (ARENA_OK);
}
