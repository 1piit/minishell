/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:10 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/20 18:01:01 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quoted_part(t_shell *sh, const char *line, int *i, char **env)
{
	char	quote;
	char	*part;
	char	*expanded;
	int		start;

	(void)env;
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
		expanded = expand_vars(sh, part, 1);
		free(part);
		return (expanded);
	}
	return (part);
}

char	*extract_unquoted_part(t_shell *sh, const char *line, int *i,
	char **env)
{
	int		start;
	char	*raw;
	char	*expanded;

	(void)env;
	start = *i;
	while (line[*i] && line[*i] != ' '
		&& !is_operator_char(line[*i])
		&& line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	raw = ft_substr(line, start, *i - start);
	if (!raw)
		return (NULL);
	expanded = expand_vars(sh, raw, 1);
	free(raw);
	return (expanded);
}

t_token	*tokenize(t_shell *sh, const char *line, char **env)
{
	int	i;
	int	op_len;

	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		op_len = handle_operator(sh, line, i);
		if (op_len > 0)
		{
			i += op_len;
			continue ;
		}
		tokenize_word(sh, line, &i, env);
	}
	return (sh->lx->head);
}

int	tokenize_word(t_shell *sh, const char *line, int *i, char **env)
{
	char	*part;
	char	*word;

	(void)env;
	word = ft_calloc(1, sizeof(char));
	if (!word)
	{
		printf("fonction: exit_all + free_all");
		return (1);
	}
	while (line[*i] && line[*i] != ' ' && !is_operator_char(line[*i]))
	{
		if (get_part(sh, line, i, &part) != 0)
		{
			free(word);
			printf("fonction: exit_all + free_all");
			return (1);
		}
		if (append_part(&word, part) != 0)
			return (printf("fonction: exit_all + free_all"), 1);
	}
	add_token(sh, T_WORD, word, 1);
	free(word);
	return (0);
}
