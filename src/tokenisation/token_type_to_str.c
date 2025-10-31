/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 16:54:01 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_type_to_str(t_tokentype type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_APPEND)
		return ("APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("INVALID");
}
