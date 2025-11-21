/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:33:06 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 21:35:43 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free_null((void **)&redir->file);
		if (redir->tmp_fd > 2)
			close(redir->tmp_fd);
		if (redir->h_fd > 2)
			close(redir->h_fd);
		free_null((void **)&redir);
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
			free_null((void **)&cmd->argv[i++]);
		free_null((void **)&cmd->argv);
	}
	free_redirs(cmd->redir);
	free_null((void **)&cmd);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free_null((void **)&head->word);
		free_null((void **)&head);
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
		free_null((void **)&tab[i]);
		i++;
	}
	free_null((void **)&tab);
}
