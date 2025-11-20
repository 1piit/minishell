/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:15:13 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/20 16:46:20 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
}

int	handle_heredoc(t_redir *r)
{
	char	*line;
	int		fd;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	fd = open(".heredoc_tmp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (perror("heredoc"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			unlink(".heredoc_tmp");
			signal(SIGINT, sigint_handler);
			return (-1);
		}
		// if (rl_done)
		// {
		// 	free(line);
		// 	close(fd);
		// }
		if (ft_strcmp(line, r->file) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd == -1)
		return (perror("heredoc"), -1);
	r->tmp_fd = fd;
	// signal(SIGINT, sigint_handler);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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

/*
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

char	*get_tmp_file_path(int index)
{
	char	*basepath;
	char	*index_str;
	char	*path;

	basepath = "/tmp/heredoc";
	index_str = ft_itoa(index);
	path = ft_strjoin(basepath, index_str);
	free(index_str);
	if (!path)
		return (NULL);
	return (path);
}

int	file_exists(char *path)
{
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}

void	clear_tmp_files(t_cmd *cmd)
{
	char	*path;
	int		index;

	index = 0;
	while (cmd)
	{
		path = get_tmp_file_path(index);
		if (!path)
			continue ;
		if (file_exists(path) == true)
			unlink(path);
		free(path);
		index++;
		cmd = cmd->next;
	}
}

static int	consume_dollar(char **res, char *str, int *i, t_shell *shell)
{
	char	*val;

	(*i)++;
	if (str[*i] == '?')
	{
		val = get_env_value(shell->env, "?", shell->exit_status);
		if (!val)
			return (-1);
		*res = ft_strjoin_free(*res, val);
		free(val);
		if (!*res)
			return (-1);
		(*i)++;
		return (1);
	}
	if (str[*i] && is_var_char(str[*i]))
	{
		if (handle_var(res, str, i, shell) == -1)
			return (-1);
		return (1);
	}
	*res = ft_strjoin_free(*res, "$");
	if (!*res)
		return (-1);
	return (1);
}

static int	append_slice(char **res, char *src, int start, int end)
{
	char	*part;

	part = ft_substr(src, start, end - start);
	if (!part)
		return (-1);
	*res = ft_strjoin_free(*res, part);
	free(part);
	if (!*res)
		return (-1);
	return (0);
}

int	create_tmp_file(int index)
{
	int		fd;
	char	*path;

	path = get_tmp_file_path(index);
	if (!path)
		return (-1);
	if (file_exists(path) == true)
	{
		fd = open(path, O_CREAT | O_TRUNC | O_WRONLY);
		if (fd == -1)
			return (free(path), -1);
		close(fd);
	}
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND);
	if (fd == -1)
		return (free(path), -1);
	return (free(path), close(fd), 0);
}

int	write_tmp_file(int index, char *line)
{
	int		fd;
	char	*path;

	path = get_tmp_file_path(index);
	if (!path)
		return (-1);
	if (file_exists(path) == false)
		return (free(path), 1);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND);
	if (fd == -1)
		return (free(path), -1);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	close(fd);
	free(path);
	return (0);
}

static int	process_step(char **res, char *str, int *i, t_shell *shell)
{
	int	c;

	c = 0;
	if (str[*i] == '$')
	{
		c = consume_dollar(res, str, i, shell);
		if (c == -1)
			return (-1);
		if (c == 1)
			return (1);
	}
	if ((unsigned char)str[*i] == 0x1C)
	{
		(*i)++;
		return (1);
	}
	if (append_slice(res, str, *i, *i + 1) == -1)
		return (-1);
	(*i)++;
	return (1);
}

char	*expand_dollar(char *str, t_shell *shell)
{
	int		i;
	char	*res;

	if (!str)
		return (ft_strdup(""));
	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (process_step(&res, str, &i, shell) == -1)
			return (free(res), NULL);
	}
	return (res);
}

char	*expand_all(char *s, t_shell *shell)
{
	char	*dup;
	char	*expanded;

	dup = ft_strdup(s);
	if (!dup)
		return (NULL);
	expanded = expand_dollar(dup, shell);
	free(dup);
	return (expanded);
}

char	*get_tmp_file_path(int index)
{
	char	*basepath;
	char	*index_str;
	char	*path;

	basepath = "/tmp/heredoc";
	index_str = ft_itoa(index);
	path = ft_strjoin(basepath, index_str);
	free(index_str);
	if (!path)
		return (NULL);
	return (path);
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
}

int	_write_to_pipes(t_cmd *cmd, int tmp_fd)
{
	char	buf[1024];
	int		size;

	while (true)
	{
		size = read(tmp_fd, buf, sizeof(buf));
		if (size <= 0)
			break ;
		write(cmd->pipe_h[1], buf, size);
	}
	return (0);
}

// Will write tmp_file content into pipe_heredoc
int	feed_pipes(t_cmd *cmd)
{
	char	*path;
	int		tmp_fd;
	int		index;

	index = 0;
	while (cmd)
	{
		path = get_tmp_file_path(index++);
		if (!path)
			return (1);
		tmp_fd = open(path, O_RDONLY);
		if (tmp_fd == -1)
			return (free(path), 1);
		if (pipe(cmd->pipe_h) == -1)
			return (close(tmp_fd), 1);
		_write_to_pipes(cmd, tmp_fd);
		close(cmd->pipe_h[1]);
		close(tmp_fd);
		free(path);
		cmd = cmd->next;
	}
	return (0);
}

// WIll ask for user input
int	execute_heredoc(t_shell *shell, t_cmd *cmd, t_redir *cur_redir,
		int tmp_index)
{
	char	*line;
	char	*line_dup;

	(void)cmd;
	signal(SIGINT, handler_heredoc);
	while (true)
	{
		signal(SIGINT, SIG_DFL);
		line = readline("> ");
		if (line == NULL || g_signal == SIGINT)
			break ;
		if (ft_strcmp(line, cur_redir->file) == 0)
		{
			free(line);
			break ;
		}
		line_dup = expand_all(line, shell);
		free(line);
		write_tmp_file(tmp_index, line_dup);
		free(line_dup);
	}
	return (0);
}

// subfunction - return child process ID
pid_t	preprocess_heredoc_cproc(t_shell *shell, t_cmd *cmd)
{
	t_redir	*tmp_redir;
	int		index;

	index = 0;
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	while (cmd)
	{
		tmp_redir = cmd->redir;
		while (tmp_redir)
		{
			if (tmp_redir->type == T_HEREDOC)
			{
				if (create_tmp_file(index) == -1)
					return (1);
				execute_heredoc(shell, cmd, tmp_redir, index);
			}
			tmp_redir = tmp_redir->next;
		}
		index++;
		cmd = cmd->next;
	}
	exit(0);
}

// Will preprocess heredoc(s) in all the cmds if any
int	preprocess_heredoc(t_shell *shell, t_cmd *cmd)
{
	if (fork() == 0)
		preprocess_heredoc_cproc(shell, cmd);
	signal(SIGINT, handler_heredoc);
	wait(NULL);
	signal(SIGINT, handle_sigint);
	feed_pipes(cmd);
	clear_tmp_files(cmd);
	if (g_signal == SIGINT)
	{
		g_signal = 1;
		shell->exit_status = 130;
		printf("> ^C\n");
	}
	return (shell->exit_status == 130);
}

*/