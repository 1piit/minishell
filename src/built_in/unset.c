/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:18:46 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/31 21:46:25 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_var2(char **env, char *var, char **new_env)
{
	int		i;
	int		j;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], var, len) == 0 && env[i][len] == '='))
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		free(env[i]);
		i++;
	}
	new_env[j] = NULL;
}

static void	unset_var(char ***env, char *var)
{
	int		count;
	char	**new_env;

	if (!env || !*env || !var)
		return ;
	count = 0;
	while ((*env)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return ;
	unset_var2(*env, var, new_env);
	free(*env);
	*env = new_env;
}

int	unset(char ***env, char **args)
{
	int	i;

	if (!env || !args)
		return (1);
	i = 0;
	while (args[i])
	{
		unset_var(env, args[i]);
		i++;
	}
	return (0);
}
