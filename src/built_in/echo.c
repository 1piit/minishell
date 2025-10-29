/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:50:18 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 16:45:29 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **av, char **alloc_env)
{
	int	i;
	int	newline;

	i = 1;
	newline = 0;
	if (!av || !av[0])
		return (1);
	if (av[i] && ft_strcmp(av[i], "-n") == 0)
	{
		newline = 1;
		i++;
	}
	echo_print_env(av, i, alloc_env);
	if (!newline)
		printf("\n");
	else
		printf(BLACK "%%" NC "\n");
	return (0);
}

char	*get_env_value(char **env, const char *var)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return ("");
}

void	echo_print_env(char **av, int i, char **alloc_env)
{
	char	*val;

	while (av[i])
	{
		if (av[i][0] == '$' && av[i][1] != '\0')
		{
			val = get_env_value(alloc_env, av[i] + 1);
			printf("%s", val);
		}
		else
			printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
}
