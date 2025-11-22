/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:11:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 06:21:34 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_shell *sh, char **envp)
{
	char	*val;

	if (!envp || !envp[0])
	{
		if (create_default_env(sh) == ERR)
			return (ERR);
		return (0);
	}
	if (copy_envp(sh, envp) == ERR)
		return (ERR);
	val = get_env_value(sh, sh->env, "HOME");
	if (!val || ft_strlen(val) == 0)
		update_env_var(&sh->env, "HOME", "/");
	free(val);
	increment_shlvl_in_env(sh);
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
