/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:02:09 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/10 18:36:47 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_cmds_pid(t_cmd *cmd, pid_t pid, char ***env)
{
	if (pid == 0)
	{
		if (setup_redirections(cmd) == -1)
			exit(1);
		if (ft_strchr(cmd->argv[0], '/'))
		{
			execve(cmd->argv[0], cmd->argv, *env);
		}
		else
		{
			execvp(cmd->argv[0], cmd->argv);
		}
		printf("Minishell: %s: %s\n", cmd->argv[0], strerror(errno));
		exit(127);
	}
}

static void	save_before_exec(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

void	execute_cmds(t_cmd *cmd, char ***env, pid_t pid)
{
	int		saved_stdout;
	int		saved_stdin;

	if (is_builtin(cmd->argv[0]))
	{
		save_before_exec(&saved_stdin, &saved_stdout);
		if (setup_redirections(cmd) == -1)
			exit(1);
		g_exit_status = exec_builtin(cmd, env);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		return ;
	}
	exec_cmds_pid(cmd, pid, env);
}
