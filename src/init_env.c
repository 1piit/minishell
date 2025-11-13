/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:11:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/12 16:46:47 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	shell_level(&env);
	return (env);
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

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	shell_level(char ***env)
{
	char	*lvl_str;
	char	*tmp;
	int		lvl;

	lvl_str = ft_getenv_shell_level("SHLVL", *env);
	if (!lvl_str)
		add_or_update_env(env, "SHLVL=1");
	else
	{
		lvl = ft_atoi(lvl_str);
		free(lvl_str);
		lvl++;
		if (lvl < 0)
			lvl = 0;
		else if (lvl > 999)
			lvl = 1;
		lvl_str = ft_itoa(lvl);

		tmp = ft_strjoin("SHLVL=", lvl_str);
		add_or_update_env(env, tmp);
		free(lvl_str);
		free(tmp);
	}
}


char	*ft_getenv_shell_level(const char *name, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}
