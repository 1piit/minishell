/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_block_registry.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:18:19 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 20:18:30 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_envp(t_shell *sh, char **envp)
{
	int	i;
	int	count;

	i = 0;
	while (envp[i])
		i++;
	count = i;
	sh->env = malloc(sizeof(char *) * (count + 1));
	if (!sh->env)
		return (ERR);
	i = 0;
	while (envp[i])
	{
		sh->env[i] = ft_strdup(envp[i]);
		if (!sh->env[i])
		{
			while (i > 0)
				free(sh->env[--i]);
			return (free(sh->env), ERR);
		}
		i++;
	}
	sh->env[i] = NULL;
	return (0);
}
