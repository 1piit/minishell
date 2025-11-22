/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:07:11 by pbride            #+#    #+#             */
/*   Updated: 2025/11/22 13:23:48 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_cmd(t_shell *sh, t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		sh->exit_status = 0;
		free_inherited_state(sh);
		_exit(sh->exit_status);
	}
	if (is_builtin(cmd->argv[0]))
		sh->exit_status = exec_builtin(sh, cmd, &sh->env);
	else
		execve_cmd(sh, cmd, &sh->env);
	free_inherited_state(sh);
	_exit(sh->exit_status);
}

void	process_childs(t_shell *sh, t_exec *exec, t_cmd *cmd,
				int (*pipes)[2])
{
	child_setup_signals_and_io(sh, exec, cmd, pipes);
	close_other_cmds_heredoc_fds(sh, cmd);
	if (pipes)
		child_close_local_pipes(pipes, exec->nb_cmds - 1);
	if (sh->exec)
	{
		free_exec_sh(sh->exec);
		sh->exec = NULL;
	}
	run_cmd(sh, cmd);
}

void	process_parent(int cmds_index, t_exec *exec, int (*pipes)[2])
{
	if (cmds_index > 0)
		close(pipes[cmds_index -1][0]);
	if (cmds_index < exec->nb_cmds - 1)
		close(pipes[cmds_index][1]);
}

static int	run_pipeline_children(t_shell *sh, t_exec *exec, t_cmd *cmd)
{
	struct termios	saved_term;
	int				saved_ok;

	saved_ok = (tcgetattr(STDIN_FILENO, &saved_term) == 0);
	spawn_and_wait(sh, exec, cmd);
	if (saved_ok)
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
	exec_destroy(exec);
	return (0);
}

int	process_pipeline(t_shell *sh, t_exec *exec, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->redir)
			if (handle_heredocs(sh, tmp->redir) == -1)
				return (-1);
		tmp = tmp->next;
	}
	exec_init(exec, cmd);
	return (run_pipeline_children(sh, exec, cmd));
}
