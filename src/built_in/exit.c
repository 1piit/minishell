/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:01:42 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/13 16:43:07 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

static bool	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (false);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static long	ft_atol(const char *s)
{
	long	sign;
	long	res;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			sign = -1;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (res > (LONG_MAX - (s[i] - '0')) / 10)
			return (false);
		res = res * 10 + (s[i++] - '0');
	}
	return (res * sign);
}

int	my_exit(char **argv)
{
	long	code;

	printf("exit\n");
	if (!argv[1])
		exit(g_exit_status);
	if (!is_numeric(argv[1]))
	{
		fprintf(stderr, "minishell: exit: %s:"
			" numeric argument required\n", argv[1]);
		exit(2);
	}
	if (argv[2])
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		return (1);
	}
	code = ft_atol(argv[1]);
	if (code > LONG_MAX || code < LONG_MIN)
	{
		fprintf(stderr, "minishell: exit: %s:"
			" numeric argument required\n", argv[1]);
		exit(2);
	}
	exit((unsigned char)code);
}
