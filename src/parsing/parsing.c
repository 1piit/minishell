/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:20:39 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/24 15:23:48 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	//if (line->type == T_APPEND && line->typ == T_REDIR_OUT)
	//	perror("Parsing error");
	//if (lx->last == NULL && lx->head->type == T_APPEND)
	//	perror();
}
