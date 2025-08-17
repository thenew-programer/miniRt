/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:11:08 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/17 12:54:04 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

static inline size_t	align_up(size_t value, size_t alignment);

void			*arena_alloc(t_arena *arena, size_t size)
{
	if (!arena)
		return ((void *)ARENA_ERROR_NULL_PARAM);
	return (arena_alloc_aligned(arena, size, arena->alignment));
}

void			*arena_alloc_aligned(t_arena *arena, size_t size, size_t alignment)
{
	void	*ptr;
	size_t	aligned_offset;

	if (!arena)
		return ((void *)ARENA_ERROR_NULL_PARAM);
	if (!size || size >= LONG_MAX)
		return ((void *)ARENA_ERROR_INVALID_SIZE);
	if (alignment == 0 || (alignment & (alignment - 1)) != 0)
		return ((void *)ARENA_ERROR_INVALID_ALIGNMENT);
	if (arena->magic != ARENA_MAGIC_NUMBER)
		return ((void *)ARENA_ERROR_CORRUPTED);

	aligned_offset = align_up(arena->offset, alignment);
	if (size > arena->size || aligned_offset > arena->size - size)
		return ((void *)ARENA_ERROR_OUT_OF_MEMORY);
	ptr = (char *)arena->buffer + aligned_offset;
	arena->offset = aligned_offset + size;
	return (ptr);
}

void			*arena_calloc(t_arena *arena, size_t size)
{
	void	*ptr;

	ptr = arena_alloc_aligned(arena, size, arena->alignment);
	if ((intptr_t)ptr <= 0)
		return (ptr);
	ft_memset(ptr, 0, size);
	return (ptr);
}

char			*arena_strdup(t_arena *arena, const char *str)
{
	size_t	size;
	void	*ptr;

	if (!str)
		return ((void *)ARENA_ERROR_NULL_PARAM);
	size = ft_strlen(str) + 1;
	ptr = arena_alloc(arena, size);
	if ((intptr_t)ptr <= 0)
		return (ptr);
	ft_memcpy(ptr, str, size);
	return (ptr);
}

static inline size_t	align_up(size_t value, size_t alignment)
{
	return ((value + alignment - 1) & ~(alignment - 1));
}
