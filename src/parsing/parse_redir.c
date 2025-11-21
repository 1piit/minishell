/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:42:06 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 22:25:53 by rgalmich         ###   ########.fr       */
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
		return (free(new), NULL);
	new->h_fd = -1;
	new->tmp_fd = -1;
	new->tmp_file = NULL;
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
		return (0);
	if (!tok->next || tok->next->type != T_WORD)
	{
		errmsg(special_count, line);
		return (-1);
	}
	new = create_redir(tok);
	if (!new)
		return (-1);
	redir_list = &cmd->redir;
	while (*redir_list)
		redir_list = &(*redir_list)->next;
	*redir_list = new;
	*current = tok->next->next;
	return (1);
}

int	parse_redirections(t_token **current, t_cmd *cmd,
				int special_count, t_token *line)
{
	int	ret;

	while (*current)
	{
		ret = process_redir_entry(current, cmd, special_count, line);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			break ;
	}
	return (0);
}
