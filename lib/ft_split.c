/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:40:51 by ymazini           #+#    #+#             */
/*   Updated: 2024/11/12 23:57:41 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*get_next_word(const char *s, char c, size_t *start)
{
	size_t	i;
	char	*word;

	while (s[*start] == c)
		(*start)++;
	i = *start;
	while (s[i] && s[i] != c)
		i++;
	word = malloc((i - *start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + *start, i - *start + 1);
	*start = i;
	return (word);
}

static char	**free_split(char **array, int size)
{
	while (size--)
		free(array[size]);
	free(array);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		words;
	size_t	i;
	size_t	pos;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < (size_t)words)
	{
		result[i] = get_next_word(s, c, &pos);
		if (!result[i])
			return (free_split(result, i));
		i++;
	}
	result[i] = NULL;
	return (result);
}
