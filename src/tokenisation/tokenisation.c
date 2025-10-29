/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:10 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 17:53:42 by rgalmich         ###   ########.fr       */
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
	if (!line[*i])
		return (fprintf(stderr, "syntax error: unclosed quote\n"), NULL);
	part = ft_substr(line, start, *i - start);
	if (!part)
		return (NULL);
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
		&& line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	raw = ft_substr(line, start, *i - start);
	if (!raw)
		return (NULL);
	expanded = expand_vars(raw, env, 1);
	free(raw);
	return (expanded);
}

t_token	*tokenize(const char *line, t_lexer *lx, char **env)
{
	int	i;
	int	op_len;

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
		tokenize_word(line, &i, lx, env);
	}
	return (lx->head);
}

int	tokenize_word(const char *line, int *i, t_lexer *lx, char **env)
{
	char	*part;
	char	*word;

	word = ft_strdup("");
	while (line[*i] && line[*i] != ' ' && !is_operator_char(line[*i]))
	{
		if (get_part(line, i, &part, env) != 0)
		{
			free(word);
			return (1);
		}
		if (append_part(&word, part) != 0)
			return (1);
	}
	add_token(lx, T_WORD, word);
	free(word);
	return (0);
}
