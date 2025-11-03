/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:34:45 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 17:56:06 by rgalmich         ###   ########.fr       */
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

int	handle_operator(const char *line, int i, t_lexer *lx)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		add_token(lx, T_APPEND, ">>");
		return (2);
	}
	if (line[i] == '<' && line[i + 1] == '<')
	{
		add_token(lx, T_HEREDOC, "<<");
		return (2);
	}
	if (line[i] == '>')
	{
		add_token(lx, T_REDIR_OUT, ">");
		return (1);
	}
	if (line[i] == '<')
	{
		add_token(lx, T_REDIR_IN, "<");
		return (1);
	}
	if (line[i] == '|')
		return (add_token(lx, T_PIPE, "|"), 1);
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

int	get_part(const char *line, int *i, char **part, char **env)
{
	if (line[*i] == '\'' || line[*i] == '"')
		*part = extract_quoted_part(line, i, env);
	else
		*part = extract_unquoted_part(line, i, env);
	if (!*part)
		return (1);
	return (0);
}
