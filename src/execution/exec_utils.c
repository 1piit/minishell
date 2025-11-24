/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:52:07 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 19:52:10 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_cmd *cmds)
{
	t_cmd	*tmp_cmds;
	int		count;

	tmp_cmds = cmds;
	count = 0;
	while (tmp_cmds)
	{
		count++;
		tmp_cmds = tmp_cmds->next;
	}
	return (count);
}

int	has_slash(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

char	*join_path(char *dir, char *cmd)
{
	size_t	dir_len;
	size_t	cmd_len;
	int		need_slash;
	char	*full_cmd_path;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	need_slash = 0;
	if (dir_len > 0 && dir[dir_len -1] != '/')
		need_slash = 1;
	full_cmd_path = malloc((dir_len + cmd_len) * sizeof(char) + need_slash + 1);
	if (!full_cmd_path)
		exit(1);
	ft_memcpy(full_cmd_path, dir, dir_len);
	if (need_slash)
		full_cmd_path[dir_len] = '/';
	ft_memcpy(full_cmd_path + dir_len + need_slash, cmd, cmd_len);
	full_cmd_path[dir_len + need_slash + cmd_len] = '\0';
	return (full_cmd_path);
}

int	is_executable_file(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	if (!S_ISREG(st.st_mode))
		return (0);
	if (access(path, X_OK) == -1)
		return (0);
	return (1);
}

char	*resolve_cmd(t_shell *sh, char **envp, char *cmd)
{
	char	*path;
	char	**dirs;
	char	**dirs_start;
	char	*full_cmd_path;

	path = get_env_value(sh, envp, "PATH");
	if (!path)
	{
		write(2, cmd, ft_strlen(cmd));
		ft_putstr_fd(": command not found\n", 2);
		free_exit_sh(sh);
		exit(127);
	}
	dirs = ft_split(path, ':');
	dirs_start = dirs;
	while (*dirs)
	{
		full_cmd_path = join_path(*dirs, cmd);
		if (is_executable_file(full_cmd_path))
			return (free_tab(dirs_start), full_cmd_path);
		free(full_cmd_path);
		dirs++;
	}
	free(path);
	return (free_tab(dirs_start), NULL);
}
