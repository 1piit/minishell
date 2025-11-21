/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:31:03 by pbride            #+#    #+#             */
/*   Updated: 2025/11/21 19:38:33 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lx_sh(t_lexer *lx)
{
	t_token	*tmp_tok;

	while (lx->head)
	{
		tmp_tok = lx->head->next;
		if (lx->head->word)
			free_null(lx->head->word);
		free_null(lx->head);
		lx->head = tmp_tok;
	}
	if (tmp_tok)
		free_null(tmp_tok);
	free_null(lx);
}

void	free_cmds_sh(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_redir;

	while (cmd)
	{
		tmp_cmd = cmd->next;
		if (cmd->argv)
			free_tab(cmd->argv);
		while (cmd->redir)
		{
			tmp_redir = cmd->redir->next;
			if (cmd->redir->file)
				free_null(cmd->redir->file);
			if (cmd->redir->tmp_file)
				free_null(cmd->redir->tmp_file);
			free_null(cmd->redir);
			cmd->redir = tmp_redir;
		}
		if (tmp_redir)
			free_null(tmp_redir);
		free_null(cmd);
		cmd = tmp_cmd;
	}
	if (tmp_cmd)
		free_null(tmp_cmd);
}

void	free_exec_sh(t_exec *exec)
{
	if (exec->pipes)
		free_null(exec->pipes);
	if (exec->pids)
		free_null(exec->pids);
	free_null(exec);
}

void	free_rdocs_sh(t_heredoc *rdoc)
{
	t_heredoc	*tmp_rdoc;

	while (rdoc)
	{
		tmp_rdoc = rdoc->next;
		if (rdoc->content)
			free_null(rdoc->content);
		if (rdoc->delimiter)
			free_null(rdoc->delimiter);
		free_null(rdoc);
		rdoc = tmp_rdoc;
	}
	if (tmp_rdoc)
		free_null(tmp_rdoc);
}
