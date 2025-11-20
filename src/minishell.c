/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:27:27 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/19 21:26:25 by rgalmich         ###   ########.fr       */
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

static void	process_line(t_lexer *lx, char *line, char ***env, t_shell *shell)
{
	t_cmd	*cmds;
	t_exec	exec;

	lexer_init(lx);
	tokenize(line, lx, *env);
	cmds = parser(lx);
	exec_init(&exec, cmds);
	if (exec.nb_cmds > 1 && cmds->next)
		process_pipeline(&exec, cmds, env, shell);
	else if (*line)
		process_one_cmd(cmds, env, shell);
	free_tokens(lx);
	lx->cmds = NULL;
	lx->head = NULL;
}

void	minishell_loop(char ***env, t_shell *shell)
{
	t_lexer	lx;
	char	*line;

	while (1)
	{
		line = readline("minishell (" VERSION ") $ ");
		if (!line)
		{
			printf("exit\n");
			rl_clear_history();
			exit(0);
		}
		if (*line)
			add_history(line);
		process_line(&lx, line, env, shell);
		free_tokens(&lx);
		free_cmd(lx.cmds);
		line[0] = '\0';
		free(line);
	}
}
