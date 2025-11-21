/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:02:57 by pbride            #+#    #+#             */
/*   Updated: 2025/11/21 19:31:43 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_exit_sh(t_shell *sh, char *mess, int code_exit)
{
	if (mess && code_exit == 0)
		printf("%s\n", mess);
	else if (mess && code_exit == 1)
		perror(mess);
	if (!sh)
		return ;
	if (sh->env)
		free_tab(sh->env);
	if (sh->lx)
		free_lx_sh(sh->lx);
	if (sh->cmds_head)
		free_cmds_sh(sh->cmds_head);
	if (sh->exec)
		free_exec_sh(sh->exec);
	if (sh->rdoc)
		free_rdocs_sh(sh->rdoc);
	exit(code_exit);
}
