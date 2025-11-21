/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:11:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 20:19:53 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* platform libc calls avoided to reduce undefined symbols */

int	init_env(t_shell *sh, char **envp)
{
	int		i;
	char	*val;

	if (!envp || !envp[0])
	{
		/* Prefer existing HOME from environment variables; if not
		   present we fallback to root to keep `cd` usable. */
		char *home = getenv("HOME");
		sh->env = malloc(sizeof(char *) * 3);
		if (!sh->env)
			return (ERR);
		if (home && ft_strlen(home) > 0)
		{
			val = ft_strjoin("HOME=", home);
			sh->env[0] = val ? val : ft_strdup("HOME=/");
		}
		else
			sh->env[0] = ft_strdup("HOME=/");
		sh->env[1] = ft_strdup("SHLVL=1");
		sh->env[2] = NULL;
		return (0);
	}
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

	val = get_env_value(sh, sh->env, "HOME");
	if (!val || ft_strlen(val) == 0)
	{
		/* Fallback: if HOME isn't present, set to root */
		update_env_var(&sh->env, "HOME", "/");
	}
	free(val);

	/* Increment or add SHLVL */
	val = get_env_value(sh, sh->env, "SHLVL");
	if (!val || ft_strlen(val) == 0)
	{
		update_env_var(&sh->env, "SHLVL", "1");
	}
	else
	{
		int lvl = ft_atoi(val);
		char *lvl_s = ft_itoa(lvl + 1);
		update_env_var(&sh->env, "SHLVL", lvl_s);
		free(lvl_s);
	}
	free(val);
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
