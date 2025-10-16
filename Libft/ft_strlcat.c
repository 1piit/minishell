/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:54:06 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 11:20:00 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	s;
	size_t	d;

	if (!dst && !src)
		return (0);
	if (siz <= ft_strlen(dst))
		return (siz + ft_strlen(src));
	s = ft_strlen(dst);
	d = 0;
	while (src[d] != '\0' && s + 1 < siz)
	{
		dst[s] = src[d];
		s++;
		d++;
	}
	dst[s] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[d]));
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char buffer[20] = "Hello";
    const char *to_append = " World!";
    size_t total;

    printf("Avant strlcat:\n");
    printf("buffer       = \"%s\"\n", buffer);
    printf("to_append    = \"%s\"\n", to_append);

    total = ft_strlcat(buffer, to_append, sizeof(buffer));

    printf("\nAprès strlcat:\n");
    printf("buffer       = \"%s\"\n", buffer);
    printf("valeur retour= %zu\n", total);

    return 0;
}
*/
