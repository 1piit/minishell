/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:33:06 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 11:32:49 by rgalmich         ###   ########.fr       */
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

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->word);
		free(head);
		head = tmp;
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
