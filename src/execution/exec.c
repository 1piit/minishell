/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:41:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/12 15:54:58 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(1);
}

void	exec_cmds_pid(t_cmd *cmd, char ***env)
{
	if (ft_strchr(cmd->argv[0], '/'))
	{
		execve(cmd->argv[0], cmd->argv, *env);
	}
	else
	{
		execvp(cmd->argv[0], cmd->argv);
	}
	printf("Minishell: %s: %s\n", cmd->argv[0], strerror(errno));
	exit(127);
}

void	execute_cmds(t_cmd *cmd, char ***env)
{
	if (is_builtin(cmd->argv[0]))
	{
		if (setup_redirections(cmd) == -1)
			exit(1);
		g_exit_status = exec_builtin(cmd, env);
		//dup2(saved_stdout, STDOUT_FILENO);
		//dup2(saved_stdin, STDIN_FILENO);
		//close(saved_stdout);
		//close(saved_stdin);
		return ;
	}
	exec_cmds_pid(cmd, env);
}
