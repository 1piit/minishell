/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:07:11 by pbride            #+#    #+#             */
/*   Updated: 2025/11/07 00:09:52 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nb_cmds - 1)
	{
		pipe(exec->pipes[i]);
		i++;
	}
}

void	close_pipes_fds(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nb_cmds - 1)
	{
		close(pipe(exec->pipes[i][0]));
		close(pipe(exec->pipes[i][1]));
	}
}
