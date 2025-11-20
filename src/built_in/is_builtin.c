/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:58:11 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/18 19:43:09 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"));
}

int	exec_builtin(t_cmd *cmd, char ***env)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (echo(cmd->argv));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (pwd());
	else if (!ft_strcmp(cmd->argv[0], "cd"))
	{
		if (cmd->argv[1])
			return (cd(cmd->argv[1], env));
		return (cd(NULL, env));
	}
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (my_exit());
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (my_env(*env));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (my_export(cmd->argv, env));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (unset(env, cmd->argv));
	return (1);
}
