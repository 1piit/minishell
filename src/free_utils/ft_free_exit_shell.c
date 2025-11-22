/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit_shell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:19:31 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 05:32:18 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lx_sh(t_lexer *lx)
{
	t_token	*tmp_tok;

	tmp_tok = NULL;
	while (lx->head)
	{
		tmp_tok = lx->head->next;
		if (lx->head->word)
			free(lx->head->word);
		free(lx->head);
		lx->head = tmp_tok;
	}
	free(lx);
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
				free(cmd->redir->file);
			if (cmd->redir->tmp_file)
				free(cmd->redir->tmp_file);
			free(cmd->redir);
			cmd->redir = tmp_redir;
		}
		free(cmd);
		cmd = tmp_cmd;
	}
}

void	free_exec_sh(t_exec *exec)
{
	if (exec->pipes)
		free(exec->pipes);
	if (exec->pids)
		free(exec->pids);
	free(exec);
}

void	free_rdocs_sh(t_heredoc *rdoc)
{
	t_heredoc	*tmp_rdoc;

	while (rdoc)
	{
		tmp_rdoc = rdoc->next;
		if (rdoc->content)
			free(rdoc->content);
		if (rdoc->delimiter)
			free(rdoc->delimiter);
		free(rdoc);
		rdoc = tmp_rdoc;
	}
}

void	free_exit_sh(t_shell *sh)
{
	if (!sh)
		return ;
	if (sh->env)
		free_tab(sh->env);
	if (sh->lx)
		free_lx_sh(sh->lx);
	if (sh->cmds_head)
		free_cmds_sh(sh->cmds_head);
	if (sh->exec)
		free_exec_sh(sh->exec);
	if (sh->rdoc)
		free_rdocs_sh(sh->rdoc);
}
