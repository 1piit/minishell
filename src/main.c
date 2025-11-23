/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:39:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 20:08:07 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	sh = (t_shell){0};
	if (init_env(&sh, envp, argv) == ERR)
		return (1);
	tcgetattr(STDIN_FILENO, &sh.g_saved_term);
	g_signal = 0;
	minishell_loop(&sh);
	free_exit_sh(&sh);
	rl_clear_history();
	printf("exit\n");
	return (g_signal);
}
