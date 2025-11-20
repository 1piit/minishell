/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:53:44 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/18 19:34:00 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_export(char **args, char ***env)
{
	int	i;
	int	j;

	i = 1;
	if (!args[i])
	{
		j = 0;
		while ((*env)[j])
		{
			printf("declare -x %s\n", (*env)[j]);
			j++;
		}
		return (0);
	}
	while (args[i])
	{
		add_or_update_env(env, args[i]);
		i++;
	}
	return (0);
}
