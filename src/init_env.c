/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:11:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 18:59:21 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <pwd.h>
#include <sys/types.h>

int	init_env(t_shell *sh, char **envp)
{
	int		i;
	char	*val;
	struct passwd *pw;

	/* If envp is NULL or empty (e.g. `env -i ./minishell`), create a
	   minimal environment with HOME and SHLVL=1 so builtins like `cd`
	   behave reasonably. */
	if (!envp || !envp[0])
	{
		pw = getpwuid(getuid());
		sh->env = malloc(sizeof(char *) * 3);
		if (!sh->env)
			return (ERR);
		if (pw && pw->pw_dir)
		{
			val = ft_strjoin("HOME=", pw->pw_dir);
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

	/* Ensure HOME exists: if not present, try to use passwd entry. */
	val = get_env_value(sh, sh->env, "HOME");
	if (!val || ft_strlen(val) == 0)
	{
		pw = getpwuid(getuid());
		if (pw && pw->pw_dir)
			update_env_var(&sh->env, "HOME", pw->pw_dir);
		else
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
