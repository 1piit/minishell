/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:17:32 by pbride            #+#    #+#             */
/*   Updated: 2025/11/23 17:38:36 by rgalmich         ###   ########.fr       */
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

void	wait_all_childs(t_shell *sh, t_exec *exec)
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
				sh->exit_status = WEXITSTATUS(status);
			else
				sh->exit_status = 1;
		}
		i++;
	}
}

void	close_other_cmds_heredoc_fds(t_shell *sh, t_cmd *cmd)
{
	t_cmd	*it;
	t_redir	*rr;

	it = sh->cmds_head;
	while (it)
	{
		if (it != cmd && it->redir)
		{
			rr = it->redir;
			while (rr)
			{
				if (rr->type == T_HEREDOC && rr->tmp_fd > 0)
				{
					close(rr->tmp_fd);
					rr->tmp_fd = -1;
				}
				rr = rr->next;
			}
		}
		it = it->next;
	}
}
