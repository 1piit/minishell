/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:20:39 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 22:18:00 by pbride           ###   ########.fr       */
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
		return (free_null((void **)&cmd), NULL);
	cmd->redir = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->next = NULL;
	argc = 0;
	while (*current && (*current)->type == T_WORD)
	{
		cmd->argv[argc] = ft_strdup((*current)->word);
		if (!cmd->argv[argc])
			return (free_cmd(cmd), NULL);
		argc++;
		*current = (*current)->next;
	}
	cmd->argv[argc] = NULL;
	return (cmd);
}

void	process_and_append(t_shell *sh, t_token **line_ptr, t_cmd **head,
					t_cmd **last)
{
	t_cmd	*cmd;
	t_token	*current;
	int		redir_status;

	current = *line_ptr;
	cmd = parse_command(&current);
	if (!cmd)
		free_exit_sh(sh, "malloc", 1);
	redir_status = parse_redirections(&current, cmd, 0, *line_ptr);
	if (redir_status == REDIR_ERR_SYNTAX)
	{
		free_cmd(cmd);
		free_exit_sh(sh, "", 1);
	}
	else if (redir_status == REDIR_ERR_ALLOC)
	{
		free_cmd(cmd);
		free_exit_sh(sh, "malloc", 1);
	}
	append_cmd(head, last, cmd);
	*line_ptr = current;
}

t_cmd	*parse_all(t_shell *sh, t_token **line_ptr)
{
	t_token	*line;
	t_cmd	*head;
	t_cmd	*last;
	int		special_count;

	line = *line_ptr;
	head = NULL;
	last = NULL;
	while (line)
	{
		special_count = 0;
		if (line->is_operator)
		{
			special_count = handle_specials(&line);
			if (special_count < 0)
				free_exit_sh(sh, "", 1);
			continue ;
		}
		process_and_append(sh, &line, &head, &last);
	}
	*line_ptr = line;
	return (head);
}

t_cmd	*parser(t_shell *sh)
{
	t_token	*line;

	line = sh->lx->head;
	return (parse_all(sh, &line));
}
