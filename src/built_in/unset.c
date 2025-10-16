/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:18:46 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/10 17:18:47 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_var2(char **env, char *var, char **new_env)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (!(ft_strncmp(env[i], var, len) == 0 && env[i][len] == '='))
		{
			new_env[j++] = ft_strdup(env[i]);
			free(env[i]);
		}
		else
			free(env[i]);
		i++;
	}
	new_env[j] = NULL;
}

void	unset_var(char ***env, char *var)
{
	int		count;
	char	**new_env;

	count = 0;
	if (!env || !*env || !var)
		return ;
	while ((*env)[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return ;
	unset_var2(*env, var, new_env);
	free(*env);
	*env = new_env;
}

void	unset(char ***env, char **args)
{
	int	i;

	i = 0;
	if (!args || !env)
		return ;
	while (args[i])
	{
		unset_var(env, args[i]);
		i++;
	}
}
