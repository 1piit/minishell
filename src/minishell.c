/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:27:27 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 18:57:57 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(t_shell *sh, char *line)
{
	t_cmd	*cmds;
	t_exec	exec;

	sh->lx = ft_calloc(1, sizeof(t_lexer));
	if (!sh->lx)
		printf("fonction: exit_all + free_all");
	tokenize(sh, line, sh->env);
	cmds = parser(sh);
	if (count_cmds(cmds) > 1 && cmds->next)
	{
		exec_init(&exec, cmds);
		process_pipeline(sh, &exec, cmds, &sh->env);
	}
	else if (count_cmds(cmds) == 1 && cmds)
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
			printf("exit\n");
			rl_clear_history();
			exit(0);
		}
		if (g_signal == SIGINT)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &sh->g_saved_term);
			if (line[0] == '\0')
			{
				free(line);
				g_signal = 0;
				continue ;
			}
			g_signal = 0;
		}
		if (*line)
			add_history(line);
		process_line(sh, line);
		free_tokens(sh->lx->head);
		free_cmd(sh->lx->cmds);
		line[0] = '\0';
		free(line);
	}
}
