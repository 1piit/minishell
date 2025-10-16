/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:23:03 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 12:35:23 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	resultat;
	int	negative;

	negative = 1;
	resultat = 0;
	while (*nptr && (*nptr == ' ' || *nptr == '\n' || *nptr == '\t'
			|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r'))
		++nptr;
	if (*nptr == '-')
		negative = -1;
	if (*nptr == '-' || *nptr == '+')
		++nptr;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		resultat = resultat * 10 + (*nptr - 48);
		++nptr;
	}
	return (resultat * negative);
}

/*
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const char *tests[] = {
        "42",
        "   -42",
        "  +123",
        "  0042",
        "   2147483647",   // INT_MAX
        "  -2147483648",   // INT_MIN
        "  +0000",
        "  +abc",
        "123abc456",
        "-+42",
        "--42",
        "",
        "   ",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++)
    {
        printf("Input: \"%s\"\n", tests[i]);
        printf("ft_atoi  : %d\n", ft_atoi(tests[i]));
        printf("atoi     : %d\n", atoi(tests[i]));
        printf("---------------------------\n");
    }

    return 0;
}
*/
