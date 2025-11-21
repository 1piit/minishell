/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:11:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/20 17:27:39 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_shell *sh, char **envp)
{
	int		i;

	if (!envp)
		return (0); // a voir ce quon fait si on doit lancer un shell sans env
	i = 0;
	while (envp[i])
		i++;
	sh->env = malloc(sizeof(char *) * (i + 1));
	if (!sh->env)
		return (ERR);
	i = 0;
	while (envp[i])
	{
		sh->env[i] = ft_strdup(envp[i]);
		i++;
	}
	sh->env[i] = NULL;
	return (0);
}

void	free_env_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
