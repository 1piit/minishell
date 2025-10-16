/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:41:57 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 11:39:07 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;
	size_t			i;

	i = 0;
	if ((!dst && !src) || n == 0)
		return (dst);
	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	while (i < n)
	{
		*(ptr_dst++) = *(ptr_src++);
		i++;
	}
	return (dst);
}

/*
#include <stdio.h>
int main(void)
{
    char src[] = "Hello World! 123";
    char dst[20];

    printf("Avant : dst = \"%s\"\n", dst);
    ft_memcpy(dst, src, 16);
    printf("Après : dst = \"%s\"\n", dst);

    return 0;
}
*/
