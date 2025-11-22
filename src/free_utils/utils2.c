/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:05:21 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 22:12:58 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_destroy(t_exec *exec)
{
	free(exec->pipes);
	free(exec->pids);
}

void	free_redir(t_redir *redir)
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

void	free_tokens_2(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->word)
			free(head->word);
		free(head);
		head = tmp;
	}
}
