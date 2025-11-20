/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:07:11 by pbride            #+#    #+#             */
/*   Updated: 2025/11/19 21:24:02 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_builtin(t_cmd *cmd, char ***env, t_shell *shell)
{
	if (is_builtin(cmd->argv[0]))
		shell->exit_status = exec_builtin(cmd, env);
	else
		execve_cmd(cmd, env);
	exit(shell->exit_status);
}

void	process_childs(t_exec *exec, t_cmd *cmd, char ***env, t_shell *shell)
{
	int	cmds_index;

	cmds_index = cmd->cmd_index;
	if (cmds_index > 0)
	{
		if (dup2(exec->pipes[cmds_index -1][0], STDIN_FILENO) == -1)
			pipeline_exit(exec, "dup2 stdin", 1);
	}
	if (cmds_index < exec->nb_cmds - 1)
	{
		if (dup2(exec->pipes[cmds_index][1], STDOUT_FILENO) == -1)
			pipeline_exit(exec, "dup2 stdout", 1);
	}
	if (setup_redirections(cmd) == -1)
		pipeline_exit(exec, "redir", 1);
	close_all_pipes_fds(exec);
	check_builtin(cmd, env, shell);
}

void	process_parent(int cmds_index, t_exec *exec)
{
	if (cmds_index > 0)
		close(exec->pipes[cmds_index -1][0]);
	if (cmds_index < exec->nb_cmds - 1)
		close(exec->pipes[cmds_index][1]);
}

void	process_pipeline(t_exec *exec, t_cmd *cmd, char ***env, t_shell *shell)
{
	int	cmds_index;

	create_pipes(exec);
	cmds_index = 0;
	while (cmd && cmds_index < exec->nb_cmds)
	{
		cmd->cmd_index = cmds_index;
		exec->pids[cmds_index] = fork();
		if (exec->pids[cmds_index] == -1)
			pipeline_exit(exec, "fork", 1);
		else if (exec->pids[cmds_index] == 0)
			process_childs(exec, cmd, env, shell);
		else
			process_parent(cmds_index, exec);
		cmds_index++;
		cmd = cmd->next;
	}
	close_all_pipes_fds(exec);
	wait_all_childs(exec, shell);
}
