/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:15:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 18:22:26 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

static void	run_heredoc_child(t_redir *r, int write_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	/* allow readline in the child to install its handlers so it properly
	   manages terminal attributes while reading the heredoc */
	rl_catch_signals = 1;
	rl_clear_history();
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, r->file) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

int	handle_heredoc(t_redir *r)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	struct termios saved_term;
	int saved_ok;

	struct sigaction	old_sa;
	struct sigaction	sa;

	saved_ok = (tcgetattr(STDIN_FILENO, &saved_term) == 0);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, &old_sa);
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
	sigaction(SIGINT, &old_sa, NULL);
	if (saved_ok)
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
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
