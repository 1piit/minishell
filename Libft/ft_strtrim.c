/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:13:18 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/29 18:39:57 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*nstr;

	start = 0;
	end = ft_strlen(s1);
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	while (end > start && is_in_set(s1[end - 1], set))
		--end;
	nstr = malloc(sizeof(char) * (end - start + 1));
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, s1 + start, end - start + 1);
	return (nstr);
}

/*
#include <stdio.h>

int	main(void)
{
	const char *str = "+++He++l+lo, wo!rld!!!+++";
	const char *set = "+!";
	char *trimmed = ft_strtrim(str, set);

	if (trimmed)
	{
		printf("Original : \"%s\"\n", str);
		printf("Trimmed  : \"%s\"\n", trimmed);
		free(trimmed);
	}
	else
	{
		printf("Erreur : trim a échoué.\n");
	}
	return (0);
}
*/
