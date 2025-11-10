/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:50:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/10 18:45:55 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_specials(t_token *line, t_token **last)
{
	t_token	*tmp;
	int		count;

	tmp = line;
	count = 0;
	while (tmp && tmp->is_operator && count < 2)
	{
		count++;
		tmp = tmp->next;
	}
	*last = tmp;
	return (count);
}

int	handle_specials(t_token **line)
{
	t_token	*after;
	int		count;

	count = count_specials(*line, &after);
	if (count > 1)
	{
		errmsg(count, *line);
		return (-1);
	}
	*line = after;
	return (count);
}

void	append_cmd(t_cmd **head, t_cmd **last, t_cmd *cmd)
{
	if (!*head)
	{
		*head = cmd;
		*last = cmd;
	}
	else
	{
		(*last)->next = cmd;
		*last = cmd;
	}
}
