/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:55:26 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 10:39:18 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main(void)
{
    const char *big = "Hello, this is a simple test";
    const char *little = "simple";
    char *result;
    size_t len = 30;

    result = ft_strnstr(big, little, len);

    if (result != NULL)
        printf("Found: \"%s\"\n", result);
    else
        printf("Not found\n");
}
*/
