/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:52:50 by rgalmich          #+#    #+#             */
/*   Updated: 2025/04/28 10:27:46 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
    char c1 = 'A';
    char c2 = 'g';
    char c3 = '!';
    
    printf("A -> %d\n", ft_isalpha(c1));  // 1
    printf("g -> %d\n", ft_isalpha(c2));  // 1
    printf("! -> %d\n", ft_isalpha(c3));  // 0
    
    return 0;
}
*/
