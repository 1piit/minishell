/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:59:20 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/27 12:36:27 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quoted_part(const char *line, int *i, char **env)
{
	char	quote;
	char	*part;
	char	*expanded;
	int		start;
	int		len;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	len = *i - start;
	if (len < 0)
		len = 0;
	part = ft_substr(line, start, len);
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
		tokenize_word(line, &i, lx, env);
	}
	return (lx->head);
}
