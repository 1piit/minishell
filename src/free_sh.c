/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:31:03 by pbride            #+#    #+#             */
/*   Updated: 2025/11/21 22:18:00 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lx_sh(t_lexer **lxp)
{
	t_lexer	*lx;
	t_token	*tmp_tok;

	if (!lxp || !*lxp)
		return ;
	lx = *lxp;
	tmp_tok = NULL;
	while (lx->head)
	{
		tmp_tok = lx->head->next;
		if (lx->head->word)
			free_null((void **)&lx->head->word);
		free_null((void **)&lx->head);
		lx->head = tmp_tok;
	}
	if (lxp && *lxp)
		free_null((void **)lxp);
}

void	free_cmds_sh(t_cmd **cmdp)
{
	t_cmd	*cmd;
	t_cmd	*tmp_cmd;
	t_redir	*tmp_redir;

	if (!cmdp || !*cmdp)
		return ;
	cmd = *cmdp;
	while (cmd)
	{
		tmp_cmd = cmd->next;
		if (cmd->argv)
			free_tab(cmd->argv);
		while (cmd->redir)
		{
			tmp_redir = cmd->redir->next;
			if (cmd->redir->file)
				free_null((void **)&cmd->redir->file);
			if (cmd->redir->tmp_file)
				free_null((void **)&cmd->redir->tmp_file);
			free_null((void **)&cmd->redir);
			cmd->redir = tmp_redir;
		}
		free_null((void **)&cmd);
		cmd = tmp_cmd;
	}
	*cmdp = NULL;
}

void	free_exec_sh(t_exec **execp)
{
	t_exec	*exec;

	if (!execp || !*execp)
		return ;
	exec = *execp;
	if (exec->pipes)
		close_all_pipes_fds(exec);
	if (exec->pipes)
		free_null((void **)&exec->pipes);
	if (exec->pids)
		free_null((void **)&exec->pids);
	*execp = NULL;
}

void	free_rdocs_sh(t_heredoc **rdocp)
{
	t_heredoc	*rdoc;
	t_heredoc	*tmp_rdoc;

	if (!rdocp || !*rdocp)
		return ;
	rdoc = *rdocp;
	while (rdoc)
	{
		tmp_rdoc = rdoc->next;
		if (rdoc->content)
			free_null((void **)&rdoc->content);
		if (rdoc->delimiter)
			free_null((void **)&rdoc->delimiter);
		free_null((void **)&rdoc);
		rdoc = tmp_rdoc;
	}
	*rdocp = NULL;
}
