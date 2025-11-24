/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:20:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 14:37:42 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_setup_signals_and_io(t_shell *sh, t_exec *exec,
		t_cmd *cmd, int (*pipes)[2])
{
	struct sigaction	sa;

	(void)sh;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	if (cmd->cmd_index > 0)
	{
		if (dup2(pipes[cmd->cmd_index - 1][0], STDIN_FILENO) == -1)
			pipeline_exit(exec, "dup2 stdin", 1);
	}
	if (cmd->cmd_index < exec->nb_cmds - 1)
	{
		if (dup2(pipes[cmd->cmd_index][1], STDOUT_FILENO) == -1)
			pipeline_exit(exec, "dup2 stdout", 1);
	}
	if (setup_redirections(cmd) == -1)
		pipeline_exit(exec, "redir", 1);
}

void	child_close_local_pipes(int (*pipes)[2], int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
