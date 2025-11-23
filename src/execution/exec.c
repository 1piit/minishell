/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:41:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 14:48:20 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_cmd_in_child(t_shell *sh, t_cmd *cmd, char ***env)
{
	pid_t			pid;
	struct termios	saved_term;
	int				saved_ok;

	saved_ok = (tcgetattr(STDIN_FILENO, &saved_term) == 0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (setup_redirections(cmd) == -1)
			return (free_and_exit(sh, 1));
		if (is_builtin(cmd->argv[0]))
		{
			sh->exit_status = exec_builtin(sh, cmd, env);
			free_and_exit(sh, sh->exit_status);
		}
		execve_cmd(sh, cmd, env);
	}
	else
		wait_child(sh, pid);
	if (saved_ok)
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
}

void	wait_child(t_shell *sh, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->exit_status = WEXITSTATUS(status);
	else
		sh->exit_status = 1;
}

void	execve_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	char		*full_cmd_path;

	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		command_not_found(NULL);
		free_and_exit(sh, 127);
	}
	if (has_slash(cmd->argv[0]) && is_executable_file(cmd->argv[0]))
	{
		execve(cmd->argv[0], cmd->argv, *env);
		perror(cmd->argv[0]);
		free_and_exit(sh, 126);
	}
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

void	process_single_cmd(t_shell *sh, t_cmd *cmd, char ***env)
{
	t_redir	*r;

	if (!cmd)
		return ;
	if (!pre_process_single_cmd(sh, cmd, env))
		return ;
	run_cmd_in_child(sh, cmd, env);
	r = cmd->redir;
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
