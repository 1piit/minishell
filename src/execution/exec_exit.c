/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:05:23 by pbride            #+#    #+#             */
/*   Updated: 2025/11/13 17:08:39 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_exit(t_exec *exec, char *err_msg, int exit_code)
{
	close_all_pipes_fds(exec);
	perror(err_msg);
	exit(exit_code);
}
