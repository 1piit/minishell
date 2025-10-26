/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:20:39 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/26 19:35:39 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parse(t_lexer *lx)
// {
// 	t_token	line;

// 	if (line->type == T_APPEND && line->type->next == T_REDIR_OUT)
// 		perror("Parsing error");
// 	if (lx->last == NULL && lx->head->type == T_APPEND)
// 		perror();
// }
/*
int	parser(t_lexer *lx)
{
	t_token	*line;
	t_token	*tmp_special;
	int		special_count;

	line = lx->head;
	tmp_special = NULL;
	special_count = 0;
	while (line && !tmp_special)
	{
		if (line->is_special)
			tmp_special = line;
		printf("line->type=%d, line->is_special=%d line->word=%s\n",
			line->type, line->is_special, line->word);
		line = line->next;
	}
	while (tmp_special && tmp_special->is_special)
	{
		special_count++;
		tmp_special = tmp_special->next;
	}
	if (special_count > 1)
		printf("Pasre error\n");
	return (0);
}
*/

int	parser(t_lexer *lx)
{
	t_token	*line;
	t_token	*tmp_special;
	int		special_count;

	line = lx->head;
	while (line)
	{
		printf(RED "line->" GREEN "type=%d" RED ", line->" GREEN "is_special=%d" RED " line->" GREEN "word=%s\n\n" NC,
			line->type, line->is_special, line->word);
		if (line->is_special)
		{
			tmp_special = line;
			special_count = 1;
			while (tmp_special->next && tmp_special->next->is_special)
			{
				special_count++;
				tmp_special = tmp_special->next;
			}
			if (special_count > 1)
			{
				printf("Parse error: %d consecutive special tokens\n",
					special_count);
				return (1);
			}
			line = tmp_special->next;
		}
		else
			line = line->next;
	}
	return (0);
}
