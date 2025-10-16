/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:02:30 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/30 11:36:55 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(char **s, size_t i)
{
	while (i--)
		free(s[i]);
	free(s);
	return (NULL);
}

static size_t	ft_countwords(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**ft_fill_split(char **split, char const *s, char c)
{
	size_t	word_len;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (ft_strchr(s, c))
				word_len = (size_t)(ft_strchr(s, c) - s);
			else
				word_len = ft_strlen(s);
			split[i] = ft_substr(s, 0, word_len);
			if (!split[i])
				return (ft_free(split, i));
			s += word_len;
			i++;
		}
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!split)
		return (NULL);
	return (ft_fill_split(split, s, c));
}

/*
#include <stdio.h>
#include <stdlib.h>

void	print_split(char **split)
{
	int i = 0;
	if (!split)
	{
		printf("NULL returned.\n");
		return;
	}
	while (split[i])
	{
		printf("Word %d: \"%s\"\n", i, split[i]);
		i++;
	}
	printf("Total words: %d\n", i);
}

int	main(void)
{
	char *tests = "Hello world this is split";
	char delimiter = ' ';
	char	**T;

	printf("Input: \"%s\"\n", tests);
	T = ft_split(tests, delimiter);
	print_split(T);
	printf("\n");
	int	j;

	j = 0;
	while (T[j])
	{
		free(T[j]);
		j++;
	}
	free(T);
	return 0;
}
*/
