/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:15:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 19:40:17 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc_child(t_redir *r, int write_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	rl_clear_history();
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, r->file) == 0)
		{
			free_null(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free_null(line);
	}
	close(write_fd);
	exit(0);
}

int	handle_heredoc(t_redir *r)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	void	(*old_sigint)(int);

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	old_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close(fd[0]);
		run_heredoc_child(r, fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, old_sigint);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (close(fd[0]), -1);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(fd[0]), -1);
	r->tmp_fd = fd[0];
	return (0);
}

int	handle_heredocs(t_redir *redir)
{
	t_redir	*r;

	r = redir;
	while (r)
	{
		if (r->type == T_HEREDOC)
			if (handle_heredoc(r) == -1)
				return (-1);
		r = r->next;
	}
	return (0);
}
