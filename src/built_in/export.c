/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:53:44 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/12 18:07:13 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

bubble_sort(char *s, int len)
{
	for (int i = 0; i < len - 1; i++)
		for (int j = 0; j < len - i - 1; j++)
			if (s[j] > s[j + 1])
				ft_swap(&s[j], &s[j + 1]);
}

*/

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
