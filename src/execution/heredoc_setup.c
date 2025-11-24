/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:52:29 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 21:07:34 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_heredoc_ctx(t_hdoc_ctx *c, t_shell *sh)
{
	t_hdoc_ctx	**ctx_ptr;

	if (pipe(c->fd) == -1)
		return (perror("pipe"), -1);
	c->cleanup_sh = sh;
	ctx_ptr = get_heredoc_ctx();
	*ctx_ptr = c;
	c->saved_ok = (tcgetattr(STDIN_FILENO, &c->saved_term) == 0);
	c->old_handler = signal(SIGINT, SIG_IGN);
	return (0);
}

int	handle_fork_error(t_hdoc_ctx *c)
{
	t_hdoc_ctx	**ctx_ptr;

	ctx_ptr = get_heredoc_ctx();
	*ctx_ptr = NULL;
	close(c->fd[0]);
	close(c->fd[1]);
	return (perror("fork"), -1);
}
