/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:39:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 17:35:47 by rgalmich         ###   ########.fr       */
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

static void	process_line(t_lexer *lx, char *line, char **env)
{
	t_cmd	*cmds;

	lexer_init(lx);
	tokenize(line, lx, env);
	cmds = parser(lx);
	if (cmds)
		execute_cmds(cmds);
}

void	execute_command(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		setup_redirections(cmd);
		if (execvp(cmd->argv[0], cmd->argv) == -1)
		{
			perror("execvp");
			exit(1);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
	}
	else
		perror("fork");
}

void	execute_cmds(t_cmd *cmds)
{
	t_cmd	*cur;

	cur = cmds;
	while (cur)
	{
		execute_command(cur);
		cur = cur->next;
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
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		process_line(&lx, line, env);
		free(line);
	}
	printf("exit\n");
	return (g_exit_status);
}
