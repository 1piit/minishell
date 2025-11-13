/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:17:32 by pbride            #+#    #+#             */
/*   Updated: 2025/11/13 18:11:04 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nb_cmds - 1)
	{
		if (pipe(exec->pipes[i]) == -1)
			pipeline_exit(exec, "pipe", 1);
		i++;
	}
}

void	close_all_pipes_fds(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nb_cmds - 1 && exec->pipes)
	{
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		i++;
	}
}

void	wait_all_childs(t_exec *exec)
{
	int		status;
	pid_t	pid;
	int		i;

	i = 0;
	while (i < exec->nb_cmds)
	{
		pid = waitpid(exec->pids[i], &status, 0);
		if (pid > 0)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else
				g_exit_status = 1;
		}
		i++;
	}
}

void	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 1;
}
