/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:20:39 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 08:46:40 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_command(t_token **current)
{
	t_cmd	*cmd;
	t_token	*tmp;
	int		count;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	tmp = *current;
	count = count_words(tmp);
	cmd->argv = malloc(sizeof(char *) * (count + 1));
	if (!cmd->argv)
		return (free(cmd), NULL);
	cmd->redir = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->next = NULL;
	if (fill_argv(cmd, current))
		return (free(cmd), NULL);
	return (cmd);
}

t_cmd	*parse_all(t_shell *sh, t_token **line_ptr)
{
	t_token	*line;
	t_cmd	*head;
	t_cmd	*last;

	(void)sh;
	line = *line_ptr;
	head = NULL;
	last = NULL;
	if (process_line_sequence(&line, &head, &last) == -1)
	{
		free_all_cmds(head);
		return (NULL);
	}
	*line_ptr = line;
	sh->cmds_head = head;
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
	if (parse_redirections(&current, cmd, 0, *line_ptr))
		return (free_cmd(cmd), 1);
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
