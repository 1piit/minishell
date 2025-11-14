/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:07:11 by pbride            #+#    #+#             */
/*   Updated: 2025/11/13 18:07:22 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_childs(int cmds_index, t_exec *exec, t_cmd *cmd, char ***env)
{
	if (cmds_index > 0)
	{
		if (dup2(exec->pipes[cmds_index -1][0], STDIN_FILENO) == -1)
			pipeline_exit(exec, "dup2 stdin", 1);
	}
	if (cmds_index < exec->nb_cmds - 1)
	{
		if (dup2(exec->pipes[cmds_index][1], STDOUT_FILENO) == -1)
			pipeline_exit(exec, "dup2 stdout", 1);
	}
	if (setup_redirections(cmd) == -1)
		pipeline_exit(exec, "redir", 1);
	close_all_pipes_fds(exec);
	if (is_builtin(cmd->argv[0]))
		g_exit_status = exec_builtin(cmd, env);
	else
		execve_cmd(cmd, env);
	exit(g_exit_status);
}

void	process_parent(int cmds_index, t_exec *exec)
{
	if (cmds_index > 0)
		close(exec->pipes[cmds_index -1][0]);
	if (cmds_index < exec->nb_cmds - 1)
		close(exec->pipes[cmds_index][1]);
}

void	process_pipeline(t_exec *exec, t_cmd *cmd, char ***env)
{
	int	cmds_index;

	create_pipes(exec);
	cmds_index = 0;
	while (cmd && cmds_index < exec->nb_cmds)
	{
		exec->pids[cmds_index] = fork();
		if (exec->pids[cmds_index] == -1)
			pipeline_exit(exec, "fork", 1);
		else if (exec->pids[cmds_index] == 0)
			process_childs(cmds_index, exec, cmd, env);
		else
			process_parent(cmds_index, exec);
		cmds_index++;
		cmd = cmd->next;
	}
	close_all_pipes_fds(exec);
	wait_all_childs(exec);
}
