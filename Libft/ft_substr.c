/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:43:30 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/29 18:57:32 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

/*
#include <stdio.h>

int main(void)
{
	const char *str = "Hello, world!";
	char *sub;

	sub = ft_substr(str, 7, 5);

	if (sub)
	{
		printf("Original : \"%s\"\n", str);
		printf("Substr   : \"%s\"\n", sub);
		free(sub);
	}
	else
	{
		printf("Erreur : substr a échoué.\n");
	}
	return 0;
}
*/
