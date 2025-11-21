/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:34:45 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/20 17:59:45 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

int	handle_operator(t_shell *sh, const char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		add_token(sh, T_APPEND, ">>", 0);
		return (2);
	}
	if (line[i] == '<' && line[i + 1] == '<')
	{
		add_token(sh, T_HEREDOC, "<<", 0);
		return (2);
	}
	if (line[i] == '>')
	{
		add_token(sh, T_REDIR_OUT, ">", 0);
		return (1);
	}
	if (line[i] == '<')
	{
		add_token(sh, T_REDIR_IN, "<", 0);
		return (1);
	}
	if (line[i] == '|')
		return (add_token(sh, T_PIPE, "|", 0), 1);
	return (0);
}

int	append_part(char **word, char *part)
{
	char	*temp;

	temp = ft_strjoin(*word, part);
	if (!temp)
	{
		free(*word);
		free(part);
		return (1);
	}
	free(*word);
	free(part);
	*word = temp;
	return (0);
}

int	get_part(t_shell *sh, const char *line, int *i, char **part)
{
	if (line[*i] == '\'' || line[*i] == '"')
		*part = extract_quoted_part(sh, line, i, sh->env);
	else
		*part = extract_unquoted_part(sh, line, i, sh->env);
	if (!*part)
		return (1);
	return (0);
}
