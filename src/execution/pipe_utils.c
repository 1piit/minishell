/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:17:32 by pbride            #+#    #+#             */
/*   Updated: 2025/11/11 16:06:09 by pbride           ###   ########.fr       */
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
		{
			close_all_pipes_fds(exec);
			perror("pipe");
			exit(1);
		}
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
