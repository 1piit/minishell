/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 06:20:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 06:22:02 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_default_env(t_shell *sh)
{
	char	*home;

	home = getenv("HOME");
	sh->env = malloc(sizeof(char *) * 3);
	if (!sh->env)
		return (ERR);
	if (home && ft_strlen(home) > 0)
	{
		sh->env[0] = ft_strjoin("HOME=", home);
		if (!sh->env[0])
			sh->env[0] = ft_strdup("HOME=/");
	}
	else
		sh->env[0] = ft_strdup("HOME=/");
	sh->env[1] = ft_strdup("SHLVL=1");
	sh->env[2] = NULL;
	return (0);
}

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
		i++;
	}
	sh->env[i] = NULL;
	return (0);
}

int	increment_shlvl_in_env(t_shell *sh)
{
	char	*val;
	int		lvl;
	char	*lvl_s;

	val = get_env_value(sh, sh->env, "SHLVL");
	if (!val || ft_strlen(val) == 0)
	{
		update_env_var(&sh->env, "SHLVL", "1");
		free(val);
		return (0);
	}
	lvl = ft_atoi(val);
	lvl_s = ft_itoa(lvl + 1);
	update_env_var(&sh->env, "SHLVL", lvl_s);
	free(lvl_s);
	free(val);
	return (0);
}
