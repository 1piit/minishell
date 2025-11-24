/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:50:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 23:48:34 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_redir(t_token *tok)
{
	if (!tok->next || tok->next->type != T_WORD)
	{
		if (tok->next && tok->next->type == T_PIPE)
			return (errmsg(tok->next), -1);
		return (errmsg(tok), -1);
	}
	return (0);
}

static int	validate_pipe(t_token *tok, int has_cmd)
{
	if (!has_cmd)
		return (errmsg(tok), -1);
	if (!tok->next)
		return (errmsg(tok), -1);
	if (tok->next->type == T_PIPE)
		return (errmsg(tok->next), -1);
	return (0);
}

int	handle_specials(t_token **line)
{
	t_token	*tok;
	int		has_cmd;

	tok = *line;
	has_cmd = 0;
	while (tok)
	{
		if (tok->type == T_WORD)
			has_cmd = 1;
		else if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
			|| tok->type == T_APPEND || tok->type == T_HEREDOC)
		{
			if (validate_redir(tok) == -1)
				return (-1);
		}
		else if (tok->type == T_PIPE)
		{
			if (validate_pipe(tok, has_cmd) == -1)
				return (-1);
			has_cmd = 0;
		}
		tok = tok->next;
	}
	return (0);
}

void	append_cmd(t_cmd **head, t_cmd **last, t_cmd *cmd)
{
	if (!*head)
	{
		*head = cmd;
		*last = cmd;
	}
	else
	{
		(*last)->next = cmd;
		*last = cmd;
	}
}
