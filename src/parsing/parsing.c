/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:20:39 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/20 16:40:20 by pbride           ###   ########.fr       */
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

t_cmd	*parse_all(t_shell *sh, t_token **line_ptr)
{
	t_token	*line;
	t_cmd	*head;
	t_cmd	*last;
	int		special_count;

	(void)sh;
	line = *line_ptr;
	head = NULL;
	last = NULL;
	sh->cmds_head = &head;
	while (line)
	{
		special_count = 0;
		if (line->is_operator)
		{
			special_count = handle_specials(&line);
			if (special_count < 0)
				return (NULL);
			continue ;
		}
		if (process_and_append(&line, &head, &last) != 0)
			return (perror("parse_command"), NULL);
	}
	*line_ptr = line;
	return (head);
}

int	process_and_append(t_token **line_ptr, t_cmd **head,
					t_cmd **last)
{
	t_cmd	*cmd;
	t_token	*current;

	current = *line_ptr;
	cmd = parse_command(&current);
	if (!cmd)
		return (1);
	parse_redirections(&current, cmd, 0, *line_ptr);
	append_cmd(head, last, cmd);
	*line_ptr = current;
	return (0);
}

t_cmd	*parser(t_shell *sh)
{
	t_token	*line;

	line = sh->lx->head;
	return (parse_all(sh, &line));
}
