/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:14:01 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 11:22:30 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *str = "Hello, world!";
    char target = 'o';
    char *result;

    result = ft_strchr(str, target);

    if (result != NULL)
        printf("Le caractère '%c' trouvé à partir de 
        : \"%s\"\n", target, result);
    else
        printf("Le caractère '%c' n'a pas été trouvé.\n", target);

    return 0;
}
*/