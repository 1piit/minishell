/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:41:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 18:59:21 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	wait_child(t_shell *sh, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else
		sh->exit_status = 1;
}

void	exec_init(t_exec *exec, t_cmd *cmd)
{
	exec->nb_cmds = count_cmds(cmd);
	exec->fd_in = 0;
	exec->fd_out = 0;
	exec->pipes = malloc((exec->nb_cmds -1) * sizeof(*exec->pipes));
	if (!exec->pipes)
		exit(1);
	exec->pids = malloc(exec->nb_cmds * sizeof(*exec->pids));
	if (!exec->pids)
		return (free(exec->pipes), exit(1));
}

void	execve_cmd(t_cmd *cmd, char ***env)
{
	char		*full_cmd_path;

	if (has_slash(cmd->argv[0]) && is_executable_file(cmd->argv[0]))
	{
		execve(cmd->argv[0], cmd->argv, *env);
		perror(cmd->argv[0]);
		exit(126);
	}
	full_cmd_path = resolve_cmd(cmd->argv[0]);
	if (!full_cmd_path)
	{
		command_not_found(cmd->argv[0]);
		free(full_cmd_path);
		exit(127);
	}
	execve(full_cmd_path, cmd->argv, *env);
	free(full_cmd_path);
	perror(cmd->argv[0]);
	exit(126);
}

void	process_single_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	pid_t	pid;

	if (cmd->redir)
		if (handle_heredocs(cmd->redir) == -1)
			return ;

	/* If there is no command (argv[0] == NULL) but there are redirections
	   (e.g. a bare heredoc like `<< DELIM`), consume/close heredoc fds and
	   do not attempt to fork/exec. This matches shell behavior where a
	   redirection-only simple_command performs no external command. */
	if (!cmd->argv || !cmd->argv[0])
	{
		t_redir *r = cmd->redir;
		while (r)
		{
			if (r->type == T_HEREDOC && r->tmp_fd > 0)
				close(r->tmp_fd);
			r = r->next;
		}
		sh->exit_status = 0;
		return ;
	}

	if (is_parent_builtin(cmd->argv[0]))
	{
		if (setup_redirections(cmd) == -1)
			exit(1);
		sh->exit_status = exec_builtin(sh, cmd, env);
	}
	else
	{
		struct termios saved_term;
		int saved_ok;

		saved_ok = (tcgetattr(STDIN_FILENO, &saved_term) == 0);
		pid = fork();
		if (pid == 0)
		{
			struct sigaction sa;

			sigemptyset(&sa.sa_mask);
			sa.sa_flags = 0;
			sa.sa_handler = SIG_DFL;
			sigaction(SIGINT, &sa, NULL);
			sa.sa_handler = SIG_DFL;
			sigaction(SIGQUIT, &sa, NULL);
			if (setup_redirections(cmd) == -1)
				exit(1);
			if (is_builtin(cmd->argv[0]))
			{
				sh->exit_status = exec_builtin(sh, cmd, env);
				exit(sh->exit_status);
			}
			else
				execve_cmd(cmd, env);
		}
		else
			wait_child(sh, pid);
		if (saved_ok)
			tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
	}
}
