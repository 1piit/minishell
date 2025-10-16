/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:27:14 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 10:43:59 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

/*
#include <stdio.h>

int main(void)
{
    const char *str = "Hello world!";
    char c = 'l';

    char *result = ft_strrchr(str, c);

    if (result)
        printf("Dernière occurrence de '%c' : \"%s\"\n", c, result);
    else
        printf("Caractère '%c' non trouvé dans la chaîne.\n", c);

    return 0;
}
*/
/*
char *ft_strrchr(const char *s, int c)
{
    int i;
	const char *y;

	y = s;
    i = ft_strlen(s);
	s = (s + i);
    while (*s != *y && c != *s)
		s--;
	if (c == *s)
		return ((char*)s);
    return (0);
}*/
