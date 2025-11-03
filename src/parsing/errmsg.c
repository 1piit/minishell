/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:30:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 17:41:03 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errmsg(int special_count, t_token *line)
{
	if (special_count <= 1)
		return (0);
	if (line->type == T_PIPE)
		printf("Minishell: syntax error near unexpected token `|'\n");
	else if (line->type == T_HEREDOC)
		printf("Minishell: syntax error near unexpected token `newline'\n");
	else if (line->type == T_APPEND)
		printf("Minishell: syntax error near unexpected token `>'\n");
	else if (line->type == T_REDIR_IN)
		printf("Minishell: syntax error near unexpected token `<'\n");
	else if (line->type == T_REDIR_OUT)
		printf("Minishell: syntax error near unexpected token `>>'\n");
	return (1);
}
