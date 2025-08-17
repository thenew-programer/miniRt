/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouryal <ybouryal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:43:33 by ybouryal          #+#    #+#             */
/*   Updated: 2025/07/22 09:53:54 by ybouryal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char *delim);
static char	*extract_word(char *str, int start, int end);
static char	**cleanup(char **words, int count, char *str);

char	**ft_dsplit(char *str, char *delim)
{
	char	**words;
	int		i[3];

	if (!str || !delim)
		return (NULL);
	words = malloc(sizeof(char *) * (count_words(str, delim) + 1));
	if (!words)
		return (free(str), NULL);
	(1) && (i[0] = 0, i[2] = 0);
	while (str[i[0]] && i[2] < count_words(str, delim))
	{
		while (str[i[0]] && ft_strchr(delim, str[i[0]]))
			i[0]++;
		if (str[i[0]])
		{
			i[1] = i[0];
			while (str[i[0]] && !ft_strchr(delim, str[i[0]]))
				i[0]++;
			words[i[2]] = extract_word(str, i[1], i[0]);
			if (!words[i[2]++])
				return (cleanup(words, i[2] - 1, str));
		}
	}
	words[i[2]] = NULL;
	return (free(str), words);
}

static int	count_words(char *str, char *delim)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(delim, str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !ft_strchr(delim, str[i]))
			i++;
	}
	return (count);
}

static char	*extract_word(char *str, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**cleanup(char **words, int count, char *str)
{
	int	i;

	i = 0;
	while (i < count)
		free(words[i++]);
	free(words);
	free(str);
	return (NULL);
}
