/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:53:44 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 17:06:53 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_var(char **env, const char *var_name)
{
	int		i;
	size_t	len;

	len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	export_no_args(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

static void	update_existing_env(char ***env, int idx, char *var)
{
	free((*env)[idx]);
	(*env)[idx] = ft_strdup(var);
}

static void	add_new_env_var(char ***env, char *var)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while ((*env) && (*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	j = 0;
	while (j < i)
	{
		new_env[j] = ft_strdup((*env)[j]);
		j++;
	}
	new_env[j] = ft_strdup(var);
	new_env[j + 1] = NULL;
	i = 0;
	while ((*env) && (*env)[i])
		free((*env)[i++]);
	free(*env);
	*env = new_env;
}

void	add_or_update_env(char ***env, char *var)
{
	int		idx;
	char	*eq;

	eq = ft_strchr(var, '=');
	if (!eq)
		return ;
	idx = find_env_var(*env, var);
	if (idx >= 0)
		update_existing_env(env, idx, var);
	else
		add_new_env_var(env, var);
}
