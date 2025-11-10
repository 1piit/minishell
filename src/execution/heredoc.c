/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:15:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/10 17:15:37 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_heredoc_to_tmp(const char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (0);
}

int	handle_heredoc(t_redir *r)
{
	int	fd;

	if (write_heredoc_to_tmp(r->file) == -1)
		return (-1);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd == -1)
		return (perror("heredoc"), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".heredoc_tmp");
	return (0);
}
