/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:53:28 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 21:04:32 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free_null((void **)&(*env)[i]);
		i++;
	}
	new_env[i++] = ft_strdup(var_value);
	new_env[i] = NULL;
	free_null((void **)env);
	*env = new_env;
}

void	update_env_var(char ***env, const char *var, const char *value)
{
	char	*tmp;
	char	*var_eq;
	int		idx;

	var_eq = ft_strjoin(var, "=");
	tmp = ft_strjoin(var_eq, value);
	free_null((void **)&var_eq);
	idx = 0;
	while ((*env)[idx])
	{
		if (ft_strncmp((*env)[idx], var, ft_strlen(var)) == 0
			&& (*env)[idx][ft_strlen(var)] == '=')
		{
			free_null((void **)&(*env)[idx]);
			(*env)[idx] = ft_strdup(tmp);
			free_null((void **)&tmp);
			return ;
		}
		idx++;
	}
	add_or_update_env(env, tmp);
	free_null((void **)&tmp);
}

int	cd(t_shell *sh, char *path, char ***env)
{
	char	cwd[4096];
	char	*home;

	if (!path || ft_strlen(path) == 0)
	{
		home = get_env_value(sh, *env, "HOME");
		if (!home || ft_strlen(home) == 0)
			return (fprintf(stderr, "Minishell: cd: HOME not set\n"), 1);
		path = home;
	}
	if (chdir(path) != 0)
		return (perror("Minishell: cd"), 1);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(env, "PWD", cwd);
	return (0);
}
