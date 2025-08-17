/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 08:56:40 by ybouryal          #+#    #+#             */
/*   Updated: 2025/05/03 09:00:48 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t size)
{
	char	*str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, size + 1);
	return (str);
}
