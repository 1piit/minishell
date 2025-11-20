/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:39:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/19 21:20:50 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	t_shell	*shell;

	shell = NULL;
	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
		return (1);
	g_exit_status = 0;
	setup_signals();
	minishell_loop(&env, shell);
	free_env_tab(env);
	clear_history();
	printf("exit\n");
	return (g_exit_status);
}
