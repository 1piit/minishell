/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:13:05 by pbride            #+#    #+#             */
/*   Updated: 2025/10/23 18:47:58 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assert_eq(int value, int expected, char *file, int line)
{
	if (value != expected)
		printf("❌%s%s:%d - %d != %d\n", RED, file, line, value, expected);
	else
		printf("✅%s%s:%d - %d == %d\n", GREEN, file, line, value, expected);
}

void	assert_str_eq(char *value, char *expected, char *file, int line)
{
	if (ft_strcmp(value, expected) != 0)
		printf("❌%s%s:%d - %s != %s\n", RED, file, line, value, expected);
	else
		printf("✅%s%s:%d - %s == %s\n", GREEN, file, line, value, expected);
}
