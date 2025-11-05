/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:20:39 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/05 17:14:11 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_specials(t_token *line, t_token **last)
{
	t_token	*tmp;
	int		count;

	tmp = line;
	count = 0;
	while (tmp && tmp->is_operator && count < 2)
	{
		count++;
		tmp = tmp->next;
	}
	*last = tmp;
	return (count);
}

int	handle_specials(t_token **line)
{
	t_token	*after;
	int		count;

	count = count_specials(*line, &after);
	if (count > 1)
	{
		errmsg(count, *line);
		return (-1);
	}
	*line = after;
	return (count);
}

t_cmd	*parse_all(t_token **line_ptr)
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
		printf("current=%s\n", line->word);
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

t_cmd	*parser(t_lexer *lx)
{
	t_token	*line;

	line = lx->head;
	return (parse_all(&line));
}
