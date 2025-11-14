/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:27:27 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/13 18:13:26 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_init(t_lexer *lx)
{
	lx->head = NULL;
	lx->last = NULL;
	lx->j = 0;
	lx->word[0] = '\0';
	lx->quote = 0;
	lx->cmds = NULL;
}

static void	process_line(t_lexer *lx, char *line, char ***env)
{
	t_cmd	*cmds;
	t_exec	exec;

	lexer_init(lx);
	tokenize(line, lx, *env);
	cmds = parser(lx);
	exec_init(&exec, cmds);
	if (exec.nb_cmds > 1 && cmds->next)
		process_pipeline(&exec, cmds, env);
	else
		process_one_cmd(cmds, env);
	free_tokens(lx);
	lx->cmds = NULL;
	lx->head = NULL;
}

void	minishell_loop(char ***env)
{
	t_lexer	lx;
	char	*line;

	while (1)
	{
		line = readline("minishell (" VERSION ") $ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		process_line(&lx, line, env);
		free_tokens(&lx);
		free_cmd(lx.cmds);
		line[0] = '\0';
		free(line);
	}
}
