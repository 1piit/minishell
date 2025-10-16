/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:27:49 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 10:42:46 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}
/*

#include <stdio.h>

int main(void)
{
    char buffer[] = "Hello World!";
    int to_find = 'o';

    char *result = ft_memchr(buffer, to_find, sizeof(buffer));

    if (result != NULL)
    {
        printf("ft_memchr a trouvé '%c' à l'adresse 
	: %p\n", *result, (void *)result);
        printf("Ce caractère est à l'index : %ld\n", result - buffer);
    }
    else
        printf("ft_memchr n'a rien trouvé.\n");

    char *ref = memchr(buffer, to_find, sizeof(buffer));
    if (ref)
        printf("memchr standard a trouvé '%c' à l'adresse 
	: %p\n", *ref, (void *)ref);

    return 0;
}

*/
