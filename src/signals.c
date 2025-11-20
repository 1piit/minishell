/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:25:44 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/20 16:48:40 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	g_signal = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int signum)
{
	(void)signum;
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_heredoc(int signum)
{
	(void)signum;
	g_signal = SIGINT;
}

void	cmd_handler(int signum)
{
	(void)signum;
	printf("\n");
	exit(130);
}
