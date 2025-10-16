/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:02:59 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 11:38:12 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_src = (const unsigned char *)src;
	if (ptr_dest > ptr_src)
		while (n--)
			ptr_dest[n] = ptr_src[n];
	else
	{
		i = 0;
		while (i < n)
		{
			ptr_dest[i] = ptr_src[i];
			i++;
		}
	}
	return (dest);
}

/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    char str1[20] = "HelloWorld";
    char str2[20] = "HelloWorld";

    // Copie normale (pas de chevauchement)
    printf("Avant (normal): %s\n", str1);
    ft_memmove(str1 + 5, str1, 5);  // Déplace "Hello" 5 cases à droite
    printf("Après ft_memmove: %s\n", str1);

    // Comparaison avec memmove standard
    memmove(str2 + 5, str2, 5);
    printf("Avec memmove   : %s\n\n", str2);

    // Cas de chevauchement en arrière
    char str3[20] = "ABCDEFGHIJ";
    char str4[20] = "ABCDEFGHIJ";

    printf("Avant (chevauchement arrière): %s\n", str3);
    ft_memmove(str3, str3 + 2, 8);  // déplace "CDEFGHIJ" vers le début
    printf("Après ft_memmove            : %s\n", str3);

    memmove(str4, str4 + 2, 8);
    printf("Avec memmove                : %s\n", str4);

    return 0;
}
*/
