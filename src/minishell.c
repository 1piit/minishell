/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:27:27 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 19:26:33 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(t_shell *sh, char *line)
{
	t_cmd	*cmds;
	t_exec	exec;

	cmds = parse_line(sh, line);
	if (!cmds)
		return ;
	if (count_cmds(cmds) > 1 && cmds->next)
		process_pipeline(sh, &exec, cmds);
	else if (count_cmds(cmds) == 1 && cmds)
		process_single_cmd(sh, cmds, &sh->env);
	g_signal = 0;
	if (sh->cmds_head)
		close_all_cmds_tmpfds(sh->cmds_head);
	free_parsed_cmds(sh);
	if (sh->cmds_head)
		sh->cmds_head = NULL;
}

static int	handle_input(t_shell *sh, char *line)
{
	if (!line)
		return (0);
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		if (line[0] == '\0')
		{
			free(line);
			g_signal = 0;
			return (1);
		}
	}
	if (*line)
		add_history(line);
	process_line(sh, line);
	if (sh->lx)
	{
		free_lx_sh(sh->lx);
		sh->lx = NULL;
	}
	line[0] = '\0';
	free(line);
	return (1);
}

void	minishell_loop(t_shell *sh)
{
	char	*line;

	setup_signals();
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &sh->g_saved_term);
		line = readline("minishell (" VERSION ") $ ");
		if (!handle_input(sh, line))
			return ;
	}
}
