/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:18:29 by ybouryal          #+#    #+#             */
/*   Updated: 2025/08/17 12:18:59 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include "../common.h"

# define ARENA_DEFAULT_ALIGNMENT	sizeof(void *)
# define ARENA_MAGIC_NUMBER			0xdeadbeef

typedef struct s_arena
{
	void		*buffer;
	size_t		size;
	size_t		offset;
	size_t		alignment;
	bool		own_buffer;
	uint32_t	magic;
	
}	t_arena;

typedef enum e_arena_error
{
	ARENA_OK = 0,
	ARENA_ERROR_NULL_PARAM = -1,
	ARENA_ERROR_INVALID_SIZE = -2,
	ARENA_ERROR_OUT_OF_MEMORY = -3,
	ARENA_ERROR_INVALID_ALIGNMENT = -4,
	ARENA_ERROR_CORRUPTED = -5
}	t_arena_error;

/* file: arena_init.c */

/*
 * Desc:
 * @arena
 * @base
 * @size
 * @alignment
 * Return:
 * */
t_arena_error	arena_init(
					t_arena *arena,
					void *base,
					size_t size,
					size_t alignment);

/*
 * Desc:
 * @arena
 * @size
 * @alignment
 * Return:
 * */
t_arena_error	arena_create(
					t_arena *arena,
					size_t	size,
					size_t alignment);

/* file: arena_mem.c */

/*
 * Desc:
 * @arena
 * @size
 * Return:
 * */
void			*arena_alloc(t_arena *arena, size_t size);

/*
 * Desc:
 * @arena
 * @size
 * @alignment
 * Return:
 * */
void			*arena_alloc_aligned(t_arena *arena, size_t size, size_t alignment);

/*
 * Desc:
 * @arena
 * @size
 * @alignment
 * Return:
 * */
void			*arena_calloc(t_arena *arena, size_t size);

/*
 * Desc:
 * @arena
 * @size
 * @alignment
 * Return:
 * */
void			*arena_calloc_aligned(t_arena *arena, size_t size, size_t alignment);

/*
 * Desc:
 * @arena
 * @str
 * Return:
 * */
char			*arena_strdup(t_arena *arena, const char *str);

/* file: arena_state.c */

/*
 * Desc:
 * @arena
 * Return:
 * */
void			arena_destroy(t_arena *arena);

/*
 * Desc:
 * @arena
 * Return:
 * */
void			arena_reset(t_arena *arena);

/*
 * Desc:
 * @arena
 * Return:
 * */
size_t			arena_available(const t_arena *arena);

/*
 * Desc:
 * @arena
 * Return:
 * */
size_t			arena_used(const t_arena *arena);

#endif /* ARENA_H */
