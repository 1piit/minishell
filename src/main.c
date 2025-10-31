/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:39:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/31 22:02:33 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

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

	lexer_init(lx);
	tokenize(line, lx, *env);
	cmds = parser(lx);
	while (cmds)
	{
		execute_cmds(cmds, env);
		cmds = cmds->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer	lx;
	char	*line;
	char	**env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
		return (1);
	g_exit_status = 0;
	while (1)
	{
		line = get_input("minishell $ ");
		process_line(&lx, line, &env);
		free(line);
	}
	printf("exit\n");
	return (g_exit_status);
}
