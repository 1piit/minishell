/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:14:10 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 10:38:49 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1[] = { (char)255, 'a', 'b', 'c', '\0' };
    char s2[] = { (char)127, 'a', 'b', 'c', '\0' };

    int std_result = strncmp(s1, s2, 1);
    int with_cast = (unsigned char)s1[0] - (unsigned char)s2[0];
    int without_cast = s1[0] - s2[0];

    printf("strncmp:       %d\n", std_result);
    printf("avec cast:     %d\n", with_cast);
    printf("sans cast:     %d\n", without_cast);
    printf("s1[0]:         %d\n", s1[0]);
    printf("s2[0]:         %d\n", s2[0]);

    return 0;
}
*/
