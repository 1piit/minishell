/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:35:33 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 18:39:31 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	heredoc_setup(t_shell *sh)
// {
// 	t_hdoc_ctx	c;
// 	t_hdoc_ctx	**ctx_ptr;

// 	c.cleanup_sh = sh;
// 	ctx_ptr = get_heredoc_ctx();
// 	*ctx_ptr = &c;
// 	c.saved_ok = (tcgetattr(STDIN_FILENO, &c.saved_term) == 0);
// 	c.old_handler = signal(SIGINT, SIG_IGN);
// 	c.pid = fork();
// }
