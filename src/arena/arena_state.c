/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:33:11 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/17 12:55:15 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void			arena_destroy(t_arena *arena)
{
	if (!arena)
		return ;
	arena->offset = 0;
	arena->size = 0;
	if (arena->own_buffer)
		free(arena->buffer);
	arena->buffer = NULL;
}

void			arena_reset(t_arena *arena)
{
	if (!arena)
		return ;
	arena->offset = 0;
}

size_t			arena_available(const t_arena *arena)
{
	size_t	avail_size;

	if (!arena)
		return (0);
	avail_size = arena->size - arena->offset;
	return (avail_size);
}

size_t			arena_used(const t_arena *arena)
{
	size_t	used_size;

	if (!arena)
		return (0);
	used_size = arena->offset;
	return (used_size);
}
