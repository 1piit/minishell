/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:53:28 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 17:37:32 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_old_env(char **new_env, char **old_env, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			return (0);
		}
		free(old_env[i]);
		i++;
	}
	return (1);
}

void	add_or_update_env(char ***env, const char *var_value)
{
	int		len;
	char	**new_env;

	if (!env || !*env || !var_value)
		return ;
	len = 0;
	while ((*env)[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return ;
	if (!copy_old_env(new_env, *env, len))
		return (free(new_env), (void)0);
	new_env[len] = ft_strdup(var_value);
	if (!new_env[len])
	{
		while (len > 0)
			free(new_env[--len]);
		free(new_env);
		return ;
	}
	new_env[len + 1] = NULL;
	free(*env);
	*env = new_env;
}

/*
void	add_or_update_env(char ***env, const char *var_value)
{
	int		i;
	int		len;
	char	**new_env;

	if (!env || !*env || !var_value)
		return ;
	len = 0;
	while ((*env)[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return ;
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new_env[i++] = ft_strdup(var_value);
	new_env[i] = NULL;
	free(*env);
	*env = new_env;
}
*/

void	update_env_var(char ***env, const char *var, const char *value)
{
	char	*tmp;
	char	*var_eq;
	int		idx;

	var_eq = ft_strjoin(var, "=");
	tmp = ft_strjoin(var_eq, value);
	free(var_eq);
	idx = 0;
	while ((*env)[idx])
	{
		if (ft_strncmp((*env)[idx], var, ft_strlen(var)) == 0
			&& (*env)[idx][ft_strlen(var)] == '=')
		{
			free((*env)[idx]);
			(*env)[idx] = tmp;
			return ;
		}
		idx++;
	}
	add_or_update_env(env, tmp);
	free(tmp);
}

int	cd(t_shell *sh, char *path, char ***env)
{
	char	cwd[4096];
	char	*home;
	t_shell	*shell;

	shell = NULL;
	if (!path || ft_strlen(path) == 0)
	{
		home = get_env_value(sh, *env, "HOME");
		if (!home || ft_strlen(home) == 0)
		{
			write(STDERR_FILENO, "Minishell: cd: HOME not set\n", 29);
			return (1);
		}
		path = home;
	}
	if (chdir(path) != 0)
		return (perror("Minishell: cd"), 1);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(env, "PWD", cwd);
	return (0);
}
