/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:15:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 11:43:48 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	finish_heredoc(t_hdoc_ctx *c, t_redir *r)
{
	waitpid(c->pid, &c->status, 0);
	signal(SIGINT, c->old_handler);
	if (c->saved_ok)
		tcsetattr(STDIN_FILENO, TCSANOW, &c->saved_term);
	if (WIFSIGNALED(c->status) && WTERMSIG(c->status) == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (close(c->fd[0]), -1);
	}
	if (WIFEXITED(c->status) && WEXITSTATUS(c->status) == 130)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (close(c->fd[0]), -1);
	}
	if (WIFEXITED(c->status) && WEXITSTATUS(c->status) == 2)
	{
		ft_putstr_fd("bash: warning: here-document at"
			"line 1 delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(r->file, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
	}
	if (r->tmp_fd > 0)
		close(r->tmp_fd);
	r->tmp_fd = c->fd[0];
	return (0);
}

static int	heredoc_loop(t_shell *sh, t_redir *r, int write_fd)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			return (2);
		}
		if (ft_strcmp(line, r->file) == 0)
		{
			free(line);
			return (0);
		}
		expanded = expand_vars(sh, line, 1);
		if (expanded)
		{
			write(write_fd, expanded, ft_strlen(expanded));
			write(write_fd, "\n", 1);
			free(expanded);
		}
		free(line);
	}
}

static void	run_heredoc_child(t_shell *sh, t_redir *r, int write_fd)
{
	int	res;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 1;
	res = heredoc_loop(sh, r, write_fd);
	close(write_fd);
	free_inherited_state(sh);
	_exit(res);
}

int	handle_heredoc(t_shell *sh, t_redir *r)
{
	t_hdoc_ctx	c;

	if (pipe(c.fd) == -1)
		return (perror("pipe"), -1);
	c.saved_ok = (tcgetattr(STDIN_FILENO, &c.saved_term) == 0);
	c.old_handler = signal(SIGINT, SIG_IGN);
	c.pid = fork();
	if (c.pid < 0)
		return (perror("fork"), -1);
	if (c.pid == 0)
	{
		close(c.fd[0]);
		run_heredoc_child(sh, r, c.fd[1]);
	}
	close(c.fd[1]);
	return (finish_heredoc(&c, r));
}

int	handle_heredocs(t_shell *sh, t_redir *redir)
{
	t_redir	*r;

	r = redir;
	while (r)
	{
		if (r->type == T_HEREDOC)
			if (handle_heredoc(sh, r) == -1)
				return (-1);
		r = r->next;
	}
	return (0);
}
