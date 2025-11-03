/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:40:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 21:34:39 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_command(t_token **current)
{
	t_cmd	*cmd;
	int		argc;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *) * 1024);
	if (!cmd->argv)
		return (free(cmd), NULL);
	cmd->redir = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->next = NULL;
	argc = 0;
	while (*current && (*current)->type == T_WORD)
	{
		cmd->argv[argc] = ft_strdup((*current)->word);
		argc++;
		*current = (*current)->next;
	}
	cmd->argv[argc] = NULL;
	return (cmd);
}

void	setup_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redir;
	while (r)
	{
		if (r->type == T_REDIR_IN)
			redir_apply_in(r);
		else if (r->type == T_REDIR_OUT)
			redir_apply_out(r);
		else if (r->type == T_APPEND)
		{
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				perror(r->file);
			else
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		r = r->next;
	}
}
