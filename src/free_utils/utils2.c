/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:05:21 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/24 14:38:00 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_destroy(t_exec *exec)
{
	if (exec->pipes)
	{
		free(exec->pipes);
		exec->pipes = NULL;
	}
	if (exec->pids)
	{
		free(exec->pids);
		exec->pids = NULL;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	tmp = NULL;
	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		if (redir->tmp_file)
			free(redir->tmp_file);
		if (redir->tmp_fd > 0)
			close(redir->tmp_fd);
		if (redir->h_fd > 0)
			close(redir->h_fd);
		free(redir);
		redir = tmp;
	}
}

void	free_tokens_2(t_token *head)
{
	t_token	*tmp;

	tmp = NULL;
	while (head)
	{
		tmp = head->next;
		if (head->word)
			free(head->word);
		free(head);
		head = tmp;
	}
}

void	free_inherited_state(t_shell *sh)
{
	if (!sh)
		return ;
	if (sh->env)
		free_tab(sh->env);
	if (sh->g_env)
		free_tab(sh->g_env);
	if (sh->cmds_head)
		free_cmds_sh(sh->cmds_head);
	if (sh->lx)
	{
		sh->lx->cmds = NULL;
		free_lx_sh(sh->lx);
	}
	if (sh->exec)
		free_exec_sh(sh->exec);
	if (sh->rdoc)
		free_rdocs_sh(sh->rdoc);
}

void	free_and_exit(t_shell *sh, int code)
{
	free_inherited_state(sh);
	exit(code);
}
