/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:52:25 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 19:52:35 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_in_child(t_shell *sh, t_cmd *cmd, char ***env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (setup_redirections(cmd) == -1)
		return (free_and_exit(sh, 1));
	if (is_builtin(cmd->argv[0]))
	{
		sh->exit_status = exec_builtin(sh, cmd, env);
		free_and_exit(sh, sh->exit_status);
	}
	execve_cmd(sh, cmd, env);
}

void	handle_parent(t_shell *sh, pid_t pid, struct termios *saved_term,
		int saved_ok)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait_child(sh, pid);
	setup_signals();
	if (saved_ok)
		tcsetattr(STDIN_FILENO, TCSANOW, saved_term);
}
