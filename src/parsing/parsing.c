/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:20:39 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/27 12:39:34 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	check_consecutive_operators(t_token *line)
{
	t_token	*tmp_operator;
	int		operator_count;

	tmp_operator = NULL;
	operator_count = 0;

	while (line && !tmp_operator)
	{
		if (line->is_operator)
			tmp_operator = line;
		line = line->next;
	}
	while (tmp_operator && tmp_operator->is_operator && operator_count < 2)
	{
		operator_count++;
		tmp_operator = tmp_operator->next;
	}
	if (operator_count > 1)
		printf("Pasre error\n");
	//TODO
	//Add exit/perror/free
}

int	parser(t_lexer *lx)
{
	t_token	*line;

	line = lx->head;
	while (line)
	{
		check_consecutive_operators(line);
		line = line->next;
	}
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
		printf(RED "line->" GREEN "type=%d" RED ", line->" GREEN
			"is_operator=%d" RED " line->" GREEN "word=%s\n\n" NC,
			line->type, line->is_operator, line->word);
		if (line->is_operator)
		{
			tmp_special = line;
			special_count = 1;
			while (tmp_special->next && tmp_special->next->is_operator)
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
