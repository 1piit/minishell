/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:33:06 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/13 13:43:02 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	free_redirs(cmd->redir);
	free(cmd);
}

void	free_all_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = NULL;
	while (cmds)
	{
		tmp = cmds->next;
		free_cmd(cmds);
		cmds = tmp;
	}
}

void	free_tokens(t_lexer *lx)
{
	t_token	*tmp;

	while (lx->head)
	{
		tmp = lx->head->next;
		free(lx->head->word);
		free(lx->head);
		lx->head = tmp;
	}
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
