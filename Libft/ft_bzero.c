/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:57:03 by rgalmich          #+#    #+#             */
/*   Updated: 2025/05/05 12:39:49 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[10] = "Hello123";
    char str2[10] = "Hello123";

    printf("Avant ft_bzero : %s\n", str1);
    ft_bzero(str1, 6);
    printf("Après ft_bzero : ");
    for (int i = 0; i < 10; i++) {
        printf("%02x ", (unsigned char)str1[i]);
    }
    printf("\n");
    memset(str2, 0, 6);
    printf("Avec memset     : ");
    for (int i = 0; i < 10; i++) {
        printf("%02x ", (unsigned char)str1[i]);
    }
    printf("\n");
    return 0;
}
*/
