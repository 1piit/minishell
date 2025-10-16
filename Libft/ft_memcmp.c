/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:42:51 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 11:13:03 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>
#include <stddef.h>

int ft_memcmp(const void *s1, const void *s2, size_t n);

int main(void)
{
    char a[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
    char b[] = { 'H', 'e', 'l', 'l', 'x', '\0' };
    char c[] = { 'H', 'e', 'l', 'l', 'o', '\0' };

    int result1 = ft_memcmp(a, b, 5);
    int result2 = ft_memcmp(a, c, 5);
    int std_result = memcmp(a, b, 5);

    printf("ft_memcmp(a, b, 5) = %d\n", result1);
    printf("ft_memcmp(a, c, 5) = %d\n", result2);
    printf("memcmp(a, b, 5)    = %d (fonction standard)\n", std_result);

    return 0;
}
*/
