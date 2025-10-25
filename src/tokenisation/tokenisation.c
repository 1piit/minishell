/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:59:20 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/25 18:37:13 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quoted_part(const char *line, int *i, char **env)
{
	char	quote;
	char	*part;
	char	*expanded;
	int		start;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	part = ft_substr(line, start, *i - start);
	if (line[*i] == quote)
		(*i)++;
	if (quote == '"')
	{
		expanded = expand_vars(part, env, 1);
		free(part);
		return (expanded);
	}
	return (part);
}

char	*extract_unquoted_part(const char *line, int *i, char **env)
{
	int		start;
	char	*raw;
	char	*expanded;

	start = *i;
	while (line[*i] && line[*i] != ' '
		&& !is_operator_char(line[*i])
		&& line[*i] != '\'' && line [*i] != '\"')
		(*i)++;
	raw = ft_substr(line, start, *i - start);
	expanded = expand_vars(raw, env, 1);
	free(raw);
	return (expanded);
}

int	tokenize_quoted_word(const char *line, int *i, t_lexer *lx)
{
	int		start;
	char	quote;
	char	*word;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i])
	{
		if (line[*i] == quote)
			break ;
		(*i)++;
	}
	if (!line[*i])
		return (fprintf(stderr, "Error: unclosed quote\n"), -1);
	word = ft_substr(line, start, *i - start);
	add_token(lx, T_WORD, word);
	free(word);
	if (line[*i] == quote)
		(*i)++;
	return (0);
}

t_token	*tokenize(const char *line, t_lexer *lx, char **env)
{
	int		i;
	int		op_len;

	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		op_len = handle_operator(line, i, lx);
		if (op_len > 0)
		{
			i += op_len;
			continue ;
		}
		if (line[i] == '\'' || line[i] == '\"')
			tokenize_quoted_word(line, &i, lx);
		else
			tokenize_word(line, &i, lx, env);
	}
	return (lx->head);
}
