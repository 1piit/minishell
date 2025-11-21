/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:42:06 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 19:40:42 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*create_redir(t_token *tok)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = tok->type;
	new->file = ft_strdup(tok->next->word);
	if (!new->file)
		return (free_null(new), NULL);
	new->next = NULL;
	return (new);
}

static int	process_redir_entry(t_token **current, t_cmd *cmd,
				int special_count, t_token *line)
{
	t_token	*tok;
	t_redir	*new;
	t_redir	**redir_list;

	tok = *current;
	if (!(tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
			|| tok->type == T_APPEND || tok->type == T_HEREDOC))
		return (REDIR_NOT_A_REDIR);
	if (!tok->next || tok->next->type != T_WORD)
	{
		errmsg(special_count, line);
		return (REDIR_ERR_SYNTAX);
	}
	new = create_redir(tok);
	if (!new)
		return (REDIR_ERR_ALLOC);
	redir_list = &cmd->redir;
	while (*redir_list)
		redir_list = &(*redir_list)->next;
	*redir_list = new;
	*current = tok->next->next;
	return (REDIR_OK);
}

int	parse_redirections(t_token **current, t_cmd *cmd,
				int special_count, t_token *line)
{
	int	redir_status;

	while (*current)
	{
		redir_status = process_redir_entry(current, cmd, special_count, line);
		if (redir_status == REDIR_NOT_A_REDIR)
			break ;
		else if (redir_status == REDIR_ERR_SYNTAX)
			return (REDIR_ERR_SYNTAX);
		else if (redir_status == REDIR_ERR_ALLOC)
			return (REDIR_ERR_ALLOC);
		else if (redir_status == REDIR_OK)
			continue ;
	}
	return (REDIR_OK);
}
