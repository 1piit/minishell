/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 06:40:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 23:54:49 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(t_token *tmp)
{
	int	count;

	count = 0;
	while (tmp && tmp->type == T_WORD)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	fill_argv(t_cmd *cmd, t_token **current)
{
	int	argc;
	int	i;

	argc = 0;
	i = 0;
	while (*current && (*current)->type == T_WORD)
	{
		cmd->argv[argc] = ft_strdup((*current)->word);
		if (!cmd->argv[argc])
		{
			while (i < argc)
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
			return (1);
		}
		argc++;
		*current = (*current)->next;
	}
	cmd->argv[argc] = NULL;
	return (0);
}

int	handle_operator_node(t_token **line, t_cmd **head, t_cmd **last)
{
	if ((*line)->type == T_REDIR_IN || (*line)->type == T_REDIR_OUT
		|| (*line)->type == T_APPEND || (*line)->type == T_HEREDOC)
	{
		if (process_and_append(line, head, last) != 0)
		{
			perror("parse_command");
			return (-1);
		}
		return (0);
	}
	if ((*line)->type == T_PIPE)
	{
		*line = (*line)->next;
		return (0);
	}
	return (0);
}

int	process_line_sequence(t_token **line, t_cmd **head, t_cmd **last)
{
	while (*line)
	{
		if ((*line)->is_operator)
		{
			if (handle_operator_node(line, head, last) == -1)
				return (-1);
			continue ;
		}
		if (process_and_append(line, head, last) != 0)
		{
			perror("parse_command");
			return (-1);
		}
	}
	return (0);
}
