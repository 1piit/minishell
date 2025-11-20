/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:17:32 by pbride            #+#    #+#             */
/*   Updated: 2025/11/20 17:23:21 by rgalmich         ###   ########.fr       */
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

void	wait_all_childs(t_exec *exec, t_shell *shell)
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
				shell->exit_status = WEXITSTATUS(status);
			else
				shell->exit_status = 1;
		}
		i++;
	}
}
