/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:39:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 21:37:21 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_at_exit(t_shell *sh)
{
	clear_history();
	sh->g_env = NULL;
}

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	sh.g_env = NULL;
	(void)argc;
	(void)argv;
	sh = (t_shell){0};
	if (init_env(&sh, envp) == ERR)
		return (1);
	sh.g_env = sh.env;
	cleanup_at_exit(&sh);
	tcgetattr(STDIN_FILENO, &sh.g_saved_term);
	g_signal = 0;
	minishell_loop(&sh);
	free_exit_sh(&sh);
	printf("exit\n");
	return (g_signal);
}
