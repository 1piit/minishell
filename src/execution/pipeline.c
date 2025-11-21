/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:07:11 by pbride            #+#    #+#             */
/*   Updated: 2025/11/21 18:22:26 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static void	run_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	if (is_builtin(cmd->argv[0]))
		sh->exit_status = exec_builtin(sh, cmd, env);
	else
		execve_cmd(cmd, env);
	exit(sh->exit_status);
}

void	process_childs(t_shell *sh, t_exec *exec, t_cmd *cmd, char ***env)
{
	int		cmds_index;

	/* child should have default signal dispositions */
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);

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
	run_cmd(sh, cmd, env);
}

void	process_parent(int cmds_index, t_exec *exec)
{
	if (cmds_index > 0)
		close(exec->pipes[cmds_index -1][0]);
	if (cmds_index < exec->nb_cmds - 1)
		close(exec->pipes[cmds_index][1]);
}

void	process_pipeline(t_shell *sh, t_exec *exec, t_cmd *cmd, char ***env)
{
	int		cmds_index;
	t_cmd	*tmp;
    struct termios saved_term;
    int saved_ok;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->redir)
			if (handle_heredocs(tmp->redir) == -1)
				return ;
		tmp = tmp->next;
	}
	create_pipes(exec);
	cmds_index = 0;
	saved_ok = (tcgetattr(STDIN_FILENO, &saved_term) == 0);
	while (cmd && cmds_index < exec->nb_cmds)
	{
		cmd->cmd_index = cmds_index;
		exec->pids[cmds_index] = fork();
		if (exec->pids[cmds_index] == -1)
			pipeline_exit(exec, "fork", 1);
		else if (exec->pids[cmds_index] == 0)
			process_childs(sh, exec, cmd, env);
		else
			process_parent(cmds_index, exec);
		cmds_index++;
		cmd = cmd->next;
	}
	close_all_pipes_fds(exec);
	wait_all_childs(sh, exec);
	if (saved_ok)
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
}
