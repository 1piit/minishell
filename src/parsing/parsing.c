/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:20:39 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/27 12:29:53 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
