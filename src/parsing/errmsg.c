/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:30:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 23:33:29 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errmsg(t_token *line)
{
	if (line->type == T_PIPE)
		write(2, "Minishell: syntax error near unexpected token `|'\n", 50);
	else if (line->type == T_HEREDOC)
		write(2, "Minishell: syntax error near unexpected"
			" token `newline'\n", 56);
	else if (line->type == T_APPEND)
		write(2, "Minishell: syntax error near unexpected token `>>'\n", 51);
	else if (line->type == T_REDIR_IN)
		write(2, "Minishell: syntax error near unexpected token `<'\n", 50);
	else if (line->type == T_REDIR_OUT)
		write(2, "Minishell: syntax error near unexpected token `>'\n", 50);
	return (0);
}
