/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:27:27 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 19:36:50 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(t_shell *sh, char *line)
{
	t_cmd	*cmds;
	t_exec	exec;

	sh->lx = ft_calloc(1, sizeof(t_lexer));
	if (!sh->lx)
		free_exit_sh(sh, "calloc", 1);
	tokenize(sh, line, sh->env);
	cmds = parser(sh);
	if (cmds && count_cmds(cmds) > 1 && cmds->next)
	{
		if (exec_init(&exec, cmds) == ERR_ALLOC)
			free_exit_sh(sh, "malloc", 1);
		process_pipeline(sh, &exec, cmds, &sh->env);
	}
	else if (cmds && count_cmds(cmds) == 1)
		process_single_cmd(sh, cmds, &sh->env);
	free_tokens(sh->lx->head);
	sh->lx->cmds = NULL;
	sh->lx->head = NULL;
}

void	minishell_loop(t_shell *sh)
{
	char	*line;

	setup_signals();
	while (1)
	{
		line = readline("minishell (" VERSION ") $ ");
		if (!line)
		{
			rl_clear_history();
			free_exit_sh(sh, "exit", 0);
		}
		if (g_signal == SIGINT)
		{
			free_null(line);
			g_signal = 0;
			continue ;
		}
		if (*line)
			add_history(line);
		process_line(sh, line);
		free_tokens(sh->lx->head);
		free_cmd(sh->lx->cmds);
		line[0] = '\0';
		free_null(line);
	}
}
