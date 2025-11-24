/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:52:18 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 19:52:40 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pre_process_single_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	if (cmd->redir)
	{
		if (handle_heredocs(sh, cmd->redir) == -1)
		{
			close_heredoc_tmpfds(cmd->redir);
			sh->exit_status = 130;
			return (0);
		}
	}
	if (!cmd->argv || !cmd->argv[0])
	{
		close_heredoc_tmpfds(cmd->redir);
		sh->exit_status = 0;
		return (0);
	}
	if (is_parent_builtin(cmd->argv[0]))
	{
		if (setup_redirections(cmd) == -1)
			exit(1);
		sh->exit_status = exec_builtin(sh, cmd, env);
		return (0);
	}
	return (1);
}

void	close_heredoc_tmpfds(t_redir *r)
{
	while (r)
	{
		if (r->type == T_HEREDOC && r->tmp_fd > 0)
		{
			close(r->tmp_fd);
			r->tmp_fd = -1;
		}
		r = r->next;
	}
}

void	exec_init(t_exec *exec, t_cmd *cmd)
{
	exec->nb_cmds = count_cmds(cmd);
	exec->fd_in = 0;
	exec->fd_out = 0;
	exec->pipes = NULL;
	exec->pids = NULL;
}

void	exec_slash_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	if (has_slash(cmd->argv[0]) && is_executable_file(cmd->argv[0]))
	{
		execve(cmd->argv[0], cmd->argv, *env);
		perror(cmd->argv[0]);
		free_and_exit(sh, 126);
	}
}

void	exec_resolved_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	char	*full_cmd_path;

	full_cmd_path = resolve_cmd(sh, *env, cmd->argv[0]);
	if (!full_cmd_path)
	{
		command_not_found(cmd->argv[0]);
		free(full_cmd_path);
		free_and_exit(sh, 127);
	}
	execve(full_cmd_path, cmd->argv, *env);
	free(full_cmd_path);
	perror(cmd->argv[0]);
	free_and_exit(sh, 126);
}
