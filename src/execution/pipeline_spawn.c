/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_spawn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:20:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 13:23:48 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	alloc_exec_arrays(t_exec *exec)
{
	exec->pids = malloc(sizeof(pid_t) * exec->nb_cmds);
	exec->pipes = NULL;
	if (exec->nb_cmds > 1)
	{
		exec->pipes = malloc(sizeof(int [2]) * (exec->nb_cmds - 1));
		if (!exec->pipes || !exec->pids)
			pipeline_exit(exec, "malloc", 1);
		create_pipes(exec);
	}
}

static void	spawn_loop(t_shell *sh, t_exec *exec, t_cmd *cmd)
{
	int	cmds_index;

	cmds_index = 0;
	while (cmd && cmds_index < exec->nb_cmds)
	{
		cmd->cmd_index = cmds_index;
		exec->pids[cmds_index] = fork();
		if (exec->pids[cmds_index] == -1)
			pipeline_exit(exec, "fork", 1);
		else if (exec->pids[cmds_index] == 0)
			process_childs(sh, exec, cmd, exec->pipes);
		else
			process_parent(cmds_index, exec, exec->pipes);
		cmds_index++;
		cmd = cmd->next;
	}
}

int	spawn_and_wait(t_shell *sh, t_exec *exec, t_cmd *cmd)
{
	alloc_exec_arrays(exec);
	spawn_loop(sh, exec, cmd);
	if (exec->pipes)
		close_all_pipes_fds(exec);
	wait_all_childs(sh, exec);
	if (exec->pipes)
		free(exec->pipes);
	free(exec->pids);
	exec->pids = NULL;
	exec->pipes = NULL;
	return (0);
}
