/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 06:20:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 20:18:15 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	alloc_default_env(t_shell *sh)
{
	char	cwd[4096];

	sh->env = malloc(sizeof(char *) * 4);
	if (!sh->env)
		return (ERR);
	if (getcwd(cwd, sizeof(cwd)))
	{
		sh->env[0] = ft_strjoin("PWD=", cwd);
		if (!sh->env[0])
		{
			sh->env[0] = ft_strdup("PWD=/");
			if (!sh->env[0])
				return (free(sh->env), ERR);
		}
	}
	else
	{
		sh->env[0] = ft_strdup("PWD=/");
		if (!sh->env[0])
			return (free(sh->env), ERR);
	}
	sh->env[3] = NULL;
	return (0);
}

static int	set_shlvl_default(t_shell *sh)
{
	sh->env[1] = ft_strdup("SHLVL=1");
	if (!sh->env[1])
		return (ERR);
	return (0);
}

static int	set_underscore_default(t_shell *sh, char *prog_name)
{
	if (prog_name)
		sh->env[2] = ft_strjoin("_=", prog_name);
	else
		sh->env[2] = ft_strdup("_=/usr/bin/env");
	if (!sh->env[2])
		return (ERR);
	return (0);
}

int	create_default_env(t_shell *sh, char *prog_name)
{
	if (alloc_default_env(sh) == ERR)
		return (ERR);
	if (set_shlvl_default(sh) == ERR)
		return (free_tab(sh->env), ERR);
	if (set_underscore_default(sh, prog_name) == ERR)
		return (free_tab(sh->env), ERR);
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
