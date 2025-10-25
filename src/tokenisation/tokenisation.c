/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:59:20 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/23 19:20:22 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		if ((line[*i] == '\\') && line[*i + 1])
		{
			*i += 2;
			continue ;
		}
		if (line[*i] == quote)
			break ;
		(*i)++;
	}
	word = ft_substr(line, start, *i - start);
	add_token(lx, T_WORD, word);
	free(word);
	if (line[*i] == quote)
		(*i)++;
	return (0);
}

t_token	*tokenize(const char *line, t_lexer *lx)
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
			tokenize_word(line, &i, lx);
	}
	return (lx->head);
}
