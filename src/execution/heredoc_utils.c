/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:38:20 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 18:22:26 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_heredoc(t_redir *r)
{
	while (r)
	{
		if (r->type == T_HEREDOC)
			return (1);
		r = r->next;
	}
	return (0);
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
}
