/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:42:06 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 17:55:08 by rgalmich         ###   ########.fr       */
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
		return (0);
	}
	new = create_redir(tok);
	if (!new)
		return (0);
	redir_list = &cmd->redir;
	while (*redir_list)
		redir_list = &(*redir_list)->next;
	*redir_list = new;
	*current = tok->next->next;
	return (1);
}

void	parse_redirections(t_token **current, t_cmd *cmd,
				int special_count, t_token *line)
{
	while (*current)
	{
		if (process_redir_entry(current, cmd, special_count, line) == 0)
			break ;
	}
}

void	redir_apply_in(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_RDONLY);
	if (fd == -1)
		perror(r->file);
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	redir_apply_out(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror(r->file);
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
