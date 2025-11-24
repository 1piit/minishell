/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:41:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 19:49:26 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_cmd_in_child(t_shell *sh, t_cmd *cmd, char ***env)
{
	pid_t			pid;
	struct termios	saved_term;
	int				saved_ok;

	saved_ok = (tcgetattr(STDIN_FILENO, &saved_term) == 0);
	pid = fork();
	if (pid == 0)
		exec_in_child(sh, cmd, env);
	else
		handle_parent(sh, pid, &saved_term, saved_ok);
}

void	wait_child(t_shell *sh, pid_t pid)
{
	int	status;
	int	sig;

	status = 0;
	waitpid(pid, &status, 0);
	sig = WTERMSIG(status);
	if (WIFSIGNALED(status))
	{
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		sh->exit_status = 128 + sig;
		return ;
	}
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else
		sh->exit_status = 1;
}

void	execve_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		command_not_found(NULL);
		free_and_exit(sh, 127);
	}
	exec_slash_cmd(sh, cmd, env);
	exec_resolved_cmd(sh, cmd, env);
}

void	process_single_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	t_redir	*r;

	if (!cmd)
		return ;
	if (!pre_process_single_cmd(sh, cmd, env))
		return ;
	run_cmd_in_child(sh, cmd, env);
	r = cmd->redir;
	while (r)
	{
		if (r->type == T_HEREDOC && r->tmp_fd > 0)
		{
			close(r->tmp_fd);
			r->tmp_fd = -1;
		}
		r = r->next;
	}
}
