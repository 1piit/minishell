/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exit_shell_parts.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 08:05:53 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 08:07:03 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit_sh_part1(t_shell *sh)
{
	if (sh->env)
		free_tab(sh->env);
	if (sh->g_env)
	{
		free_tab(sh->g_env);
		sh->g_env = NULL;
	}
	if (sh->lx)
		free_lx_sh(sh->lx);
}

void	free_exit_sh_part2(t_shell *sh)
{
	if (sh->cmds_head)
		free_cmds_sh(sh->cmds_head);
	if (sh->exec)
		free_exec_sh(sh->exec);
	if (sh->rdoc)
		free_rdocs_sh(sh->rdoc);
	if (sh->stdin_backup > 2)
		close(sh->stdin_backup);
	if (sh->stdout_backup > 2)
		close(sh->stdout_backup);
	sh->env = NULL;
	sh->lx = NULL;
	sh->cmds_head = NULL;
	sh->exec = NULL;
	sh->rdoc = NULL;
}
