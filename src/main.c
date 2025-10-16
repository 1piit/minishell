/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:21:11 by rgalmich          #+#    #+#             */
/*   Updated: 2025/09/28 15:21:13 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	main(int ac, char **av, char **envp)
{
	char	**alloc_env;

	(void)ac;
	(void)av;
	alloc_env = init_env(envp);
	if (!alloc_env)
		return (1);
	handle_signals();
	minishell_loop(alloc_env);
	free_env(alloc_env);
	return (0);
}
*/
int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	cwd[4096];
	char	prompt[512];
	char	**args;
	int		len;
	char	**alloc_env;
	int		i;
	int		j;

	(void)ac;
	(void)av;
	len = 0;
	i = 0;
	while (envp[i])
		i++;
	alloc_env = malloc(sizeof(char *) * (i + 1));
	if (!alloc_env)
		return (1);
	j = 0;
	while (j < i)
	{
		alloc_env[j] = ft_strdup(envp[j]);
		j++;
	}
	alloc_env[j] = NULL;
	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			ft_strcpy(prompt, PURPLE_DARK "minishell " VERSION BLUE_DARK " (");
			ft_strcpy(prompt + ft_strlen(prompt), cwd);
			ft_strcpy(prompt + ft_strlen(prompt), ")$ " NC);
		}
		else
			ft_strcpy(prompt, PURPLE_DARK
				"minishell " VERSION BLUE_DARK " (unknown)$ " NC);
		line = readline(prompt);
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);

			args = ft_split(line, ' ');
			if (!args)
			{
				free(line);
				continue ;
			}
			if (ft_strcmp(args[0], "cd") == 0)
				cd(args[1]);
			else if (ft_strcmp(args[0], "pwd") == 0)
				pwd();
			else if (ft_strcmp(args[0], "env") == 0)
				env(alloc_env);
			else if (ft_strcmp(args[0], "echo") == 0)
				echo(args, alloc_env);
			else if (ft_strncmp(args[0], "unset", 5) == 0)
				unset(&alloc_env, args);
			else if (ft_strcmp(args[0], "export") == 0)
			{
				if (!args[1])
					export_no_args(alloc_env);
				else
				{
					int i = 1;
					while (args[i])
					{
						add_or_update_env(&alloc_env, args[i]);
						i++;
					}
				}
			}
			else if (ft_strcmp(args[0], "exit") == 0)
			{
				free(line);
				free(args);
				break ;
			}
			else
				printf("Command not found: %s\n", args[0]);

			free(args);
		}
		free(line);
	}
	return (0);
}
