/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:00:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 11:50:42 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pre_process_single_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	if (cmd->redir)
	{
		if (handle_heredocs(sh, cmd->redir) == -1)
		{
			close_heredoc_tmpfds(cmd->redir);
			return (0);
		}
	}
	if (!cmd->argv || !cmd->argv[0])
	{
		close_heredoc_tmpfds(cmd->redir);
		sh->exit_status = 0;
		return (0);
	}
	if (is_parent_builtin(cmd->argv[0]))
	{
		if (setup_redirections(cmd) == -1)
			exit(1);
		sh->exit_status = exec_builtin(sh, cmd, env);
		return (0);
	}
	return (1);
}

void	close_heredoc_tmpfds(t_redir *r)
{
	while (r)
	{
		if (r->type == T_HEREDOC && r->tmp_fd > 0)
		{
			close(r->tmp_fd);
			r->tmp_fd = -1;
		}
		r = r->next;
	}
}
