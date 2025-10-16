/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:49:21 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/10 13:49:24 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **envp)
{
	int	i;

	if (!envp)
		return (fprintf(stderr, "env: no environment found\n"));
	i = 0;
	while (envp[i])
	{
		printf(WHITE "%s\n" NC, envp[i]);
		i++;
	}
	return (0);
}
