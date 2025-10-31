/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:53:40 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 16:53:41 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **envp)
{
	int	i;

	if (!envp)
	{
		fprintf(stderr, "env: no environment found\n");
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		printf(WHITE "%s\n" NC, envp[i]);
		i++;
	}
	return (0);
}
