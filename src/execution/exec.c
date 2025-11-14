/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:41:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/13 18:09:13 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_exec *exec, t_cmd *cmd)
{
	exec->nb_cmds = count_cmds(cmd);
	exec->fd_in = 0;
	exec->fd_out = 0;
	if (exec->nb_cmds > 1)
	{
		exec->pipes = malloc((exec->nb_cmds -1) * sizeof(*exec->pipes));
		if (!exec->pipes)
			exit(1);
	}
	else
		exec->pipes = NULL;
	exec->pids = malloc(exec->nb_cmds * sizeof(*exec->pids));
	if (!exec->pids)
		exit(1);
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
		perror(cmd->argv[0]);
		free(full_cmd_path);
		exit(127);
	}
	execve(full_cmd_path, cmd->argv, *env);
	free(full_cmd_path);
	perror(cmd->argv[0]);
	exit(126);
}

void	process_one_cmd(t_cmd *cmd, char ***env)
{
	pid_t	pid;

	if (is_parent_builtin(cmd->argv[0]))
	{
		if (setup_redirections(cmd) == -1)
			exit(1);
		g_exit_status = exec_builtin(cmd, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (setup_redirections(cmd) == -1)
				exit(1);
			if (is_builtin(cmd->argv[0]))
				g_exit_status = exec_builtin(cmd, env);
			else
				execve_cmd(cmd, env);
		}
		else
			wait_child(pid);
	}
}
