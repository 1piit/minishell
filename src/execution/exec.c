/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:41:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 06:58:58 by rgalmich         ###   ########.fr       */
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
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (setup_redirections(cmd) == -1)
			exit(1);
		if (is_builtin(cmd->argv[0]))
		{
			sh->exit_status = exec_builtin(sh, cmd, env);
			exit(sh->exit_status);
		}
		execve_cmd(cmd, env);
	}
	else
		wait_child(sh, pid);
	if (saved_ok)
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
}

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

	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		command_not_found(NULL);
		exit(127);
	}
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
	t_redir	*r;

	if (cmd->redir)
		if (handle_heredocs(sh, cmd->redir) == -1)
			return ;
	if (!cmd->argv || !cmd->argv[0])
	{
		r = cmd->redir;
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
		return ;
	}
	run_cmd_in_child(sh, cmd, env);
}
