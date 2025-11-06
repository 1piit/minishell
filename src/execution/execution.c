/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:41:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/07 00:36:36 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_exec *exec, t_cmd *cmd)
{
	exec->nb_cmds = count_cmds(cmd);
	exec->fd_in = 0;
	exec->fd_out = 0;
	exec->pipes = malloc(exec->nb_cmds * sizeof(*exec->pipes));
	if (!exec->pipes)
		exit(1);
	exec->pids = malloc(exec->nb_cmds * sizeof(*exec->pids));
	if (!exec->pids)
		exit(1);
}

void	wait_all_childs(t_exec *exec)
{
	int		status;
	pid_t	pid;
	int		i;

	i = 0;
	while (i < exec->nb_cmds)
	{
		pid = wait(&status);
		if (!pid)
		{
			perror("wait pid");
			exit(1);
		}
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 1;
		printf("Fork [%i] terminé avec le code %i\n", pid, status);
		i++;
	}
}

void	process_pipeline(t_exec *exec, t_cmd *cmds, char **env)
{
	int	j;

	j = 0;
	while (cmds && j < exec->nb_cmds)
	{
		exec->pids[j] = fork();
		if (exec->pids[j] == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (exec->pids[j] == 0)
		{
			printf("Process enfant: pid=%d\n", exec->pids[j]);
			if (j > 0)
			{
				if (dup2(exec->pipes[j - 1][0], STDIN_FILENO) == -1)
				{
					perror("dup2 stdin");
					exit(1);
				}
			}
			if (j < exec->nb_cmds - 1)
			{
				if (dup2(exec->pipes[j][1], STDOUT_FILENO) == -1)
				{
					perror("dup2 stdout");
					exit(1);
				}
			}
			close_pipes_fds(exec);
			//1)Creer les redirections ici
			//2)Lancer l'exec
			// => a checker cette fonction, possible de recuperer en modifiant un peu
			//execute_cmds()
		}
		else
		{
			printf("Process parent: pid=%d\n", exec->pids[j]);
			if (j > 0)
				close(pipes(exec->pipes[j - 1][0]));
			if (j < exec->nb_cmds - 1)
				close(pipes(exec->pipes[j][1]));
		}
		j++;
		cmds = cmds->next;
	}
	close_pipes_fds(exec);
	wait_all_childs(exec);
	printf("j=%d\n", j);
	//wait_all_childs(exec);
	//printf("nb_cmds=%d\n", exec->nb_cmds);
	//int i = 0;
	//while (i < exec->nb_cmds)
	//{
	//	int j = 0;
	//	while (j < 2)
	//	{
	//		printf("1");
	//		j++;
	//	}
	//	printf("\n");
	//	i++;
	//}
	(void)env;
}

//void	wait_for_child(pid_t pid)
//{
//	int	status;

//	waitpid(pid, &status, 0);
//	if (WIFEXITED(status))
//	{
//		g_exit_status = WEXITSTATUS(status);
//	}
//	else
//	{
//		g_exit_status = 1;
//	}
//}
