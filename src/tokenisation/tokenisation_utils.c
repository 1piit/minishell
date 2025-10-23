/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:34:45 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/23 12:34:46 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*add_token(t_lexer *lx, t_tokentype type, char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->word = NULL;
	if (word)
	{
		new->word = ft_strdup(word);
		if (!new->word)
			return (free(new), NULL);
	}
	new->next = NULL;
	if (lx->head == NULL)
		lx->head = new;
	else
		(lx->last)->next = new;
	lx->last = new;
	return (new);
}

int	handle_operator(const char *line, int i, t_lexer *lx)
{
	if (line [i] == '>' && line[i + 1] == '>')
		return (add_token(lx, T_APPEND, ">>"), 2);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (add_token(lx, T_HEREDOC, "<<"), 2);
	else if (line[i] == '>')
		return (add_token(lx, T_REDIR_OUT, ">"), 1);
	else if (line[i] == '<')
		return (add_token(lx, T_REDIR_IN, "<"), 1);
	else if (line[i] == '|')
		return (add_token(lx, T_PIPE, "|"), 1);
	return (0);
}

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	tokenize_word(const char *line, int *i, t_lexer *lx)
{
	int		start;
	char	*word;

	start = *i;
	while (line[*i] && line[*i] != ' ' && !is_operator_char(line[*i]))
		(*i)++;
	word = ft_substr(line, start, *i - start);
	add_token(lx, T_WORD, word);
	free(word);
	return (0);
}
