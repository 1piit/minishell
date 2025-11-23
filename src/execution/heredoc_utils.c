/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:38:20 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 18:04:11 by rgalmich         ###   ########.fr       */
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

void	setup_signals_heredoc(void)
{
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 1;
}

t_hdoc_ctx	**get_heredoc_ctx(void)
{
	static t_hdoc_ctx	*ctx;

	return (&ctx);
}

void	heredoc_signal_cleanup(void)
{
	t_hdoc_ctx	**ctx_ptr;

	ctx_ptr = get_heredoc_ctx();
	if (*ctx_ptr && (*ctx_ptr)->cleanup_sh)
	{
		free_inherited_state((*ctx_ptr)->cleanup_sh);
		(*ctx_ptr)->cleanup_sh = NULL;
	}
}
