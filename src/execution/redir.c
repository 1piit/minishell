/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:13:42 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/12 15:03:29 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_apply_in(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_RDONLY);
	if (fd == -1)
		return (perror(r->file), -1);
	dup2(fd, STDIN_FILENO);
	//bien les proteger les dup2 comme dans le process enfant
	close(fd);
	return (0);
}

int	redir_apply_out(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(r->file), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_append(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(r->file), -1);
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		perm_file;

	r = cmd->redir;
	while (r)
	{
		if (r->type == T_REDIR_IN)
			perm_file = redir_apply_in(r);
		else if (r->type == T_REDIR_OUT)
			perm_file = redir_apply_out(r);
		else if (r->type == T_APPEND)
			perm_file = apply_append(r);
		else if (r->type == T_HEREDOC)
			perm_file = handle_heredoc(r);
		if (perm_file == -1)
			return (-1);
		r = r->next;
	}
	return (0);
}
