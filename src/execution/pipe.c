/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:07:11 by pbride            #+#    #+#             */
/*   Updated: 2025/11/12 15:53:13 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_childs(int cmds_index, t_exec *exec, t_cmd *cmds, char ***env)
{
	if (cmds_index > 0)
	{
		if (dup2(exec->pipes[cmds_index -1][0], STDIN_FILENO) == -1)
		{
			close_all_pipes_fds(exec);
			perror("dup2 stdin");
			exit(1);
		}
	}
	if (cmds_index < exec->nb_cmds - 1)
	{
		if (dup2(exec->pipes[cmds_index][1], STDOUT_FILENO) == -1)
		{
			close_all_pipes_fds(exec);
			perror("dup2 stdout");
			exit(1);
		}
	}
	if (setup_redirections(cmds) == -1)
		exit(1);
	close_all_pipes_fds(exec);
	execute_cmds(cmds, env);
	exit(g_exit_status);
}

void	process_parent(int cmds_index, t_exec *exec)
{
	if (cmds_index > 0)
		close(exec->pipes[cmds_index -1][0]);
	if (cmds_index < exec->nb_cmds - 1)
		close(exec->pipes[cmds_index][1]);
}

void	process_pipeline(t_exec *exec, t_cmd *cmds, char ***env)
{
	int	cmds_index;

	create_pipes(exec);
	cmds_index = 0;
	while (cmds && cmds_index < exec->nb_cmds)
	{
		exec->pids[cmds_index] = fork();
		if (exec->pids[cmds_index] == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (exec->pids[cmds_index] == 0)
			process_childs(cmds_index, exec, cmds, env);
		else
			process_parent(cmds_index, exec);
		cmds_index++;
		cmds = cmds->next;
	}
	close_all_pipes_fds(exec);
	wait_all_childs(exec);
}
