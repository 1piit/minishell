/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:31:11 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/29 13:18:32 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/*
#include <stdio.h>

int main(void)
{
    char dest1[20];
    char dest2[5];
    char *src = "HelloWorld";

    // Cas 1 : assez d'espace
    size_t len1 = ft_strlcpy(dest1, src, sizeof(dest1));
    printf("Cas 1 - Assez d'espace:\n");
    printf("Résultat : %s\n", dest1);
    printf("Retour   : %zu (longueur de src)\n\n", len1);

    // Cas 2 : espace insuffisant
    size_t len2 = ft_strlcpy(dest2, src, sizeof(dest2));
    printf("Cas 2 - Espace insuffisant:\n");
    printf("Résultat : %s\n", dest2);
    printf("Retour   : %zu (longueur de src)\n\n", len2);

    // Cas 3 : taille 0
    size_t len3 = ft_strlcpy(dest1, src, 0);
    printf("Cas 3 - dstsize = 0:\n");
    printf("Retour : %zu (longueur de src)\n\n", len3);

    return 0;
}
*/
