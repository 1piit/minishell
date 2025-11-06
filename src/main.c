/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:39:17 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/06 23:01:37 by pbride           ###   ########.fr       */
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
	//t_cmd	*tmp;
	t_exec	exec;

	lexer_init(lx);
	tokenize(line, lx, *env);
	//print_tokens(lx);
	//printf("before parser\n");
	cmds = parser(lx);
	//printf("before exec_init\n");
	//print_cmds(cmds);
	exec_init(&exec, cmds);
	//printf("before process_pipeline\n");
	process_pipeline(&exec, cmds, *env);
	//while (cmds)
	//{
	//	tmp = cmds->next;
	//	execute_cmds(cmds, env);
	//	free_cmd(cmds);
	//	cmds = tmp;
	//}
	free_tokens(lx);
	lx->cmds = NULL;
	lx->head = NULL;
}
/*
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
			fprintf(stderr, "Minishell: command not found: "
				"%s\n", cmd->argv[0]);
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
*/

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
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell (" VERSION ") $ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		process_line(&lx, line, &env);
		free_tokens(&lx);
		free_cmd(lx.cmds);
		line[0] = '\0';
		free(line);
	}
	free_env_tab(env);
	clear_history();
	printf("exit\n");
	return (g_exit_status);
}
