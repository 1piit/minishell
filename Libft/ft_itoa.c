/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:31:32 by rgalmich          #+#    #+#             */
/*   Updated: 2025/05/05 12:44:58 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int		len;
	long	nb;

	len = (n <= 0);
	nb = n;
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		len;

	len = ft_intlen(n);
	nb = n;
	if (nb < 0)
		nb = -nb;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > (n < 0))
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

/*
#include <stdio.h>
int main(void)
{
    printf("itoa(42) = %s\n", ft_itoa(42));
    printf("itoa(-1234) = %s\n", ft_itoa(-1234));
    printf("itoa(0) = %s\n", ft_itoa(0));
    printf("itoa(-2147483648) = %s\n", ft_itoa(-2147483648));
    printf("itoa(2147483647) = %s\n", ft_itoa(2147483647));
}
*/
