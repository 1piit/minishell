/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:01:42 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/31 20:05:27 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	my_exit(char **argv)
{
	int	status;

	status = g_exit_status;
	if (argv[1])
		status = ft_atoi(argv[1]);
	printf("exit\n");
	exit(status);
}
