/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:05:23 by pbride            #+#    #+#             */
/*   Updated: 2025/11/22 08:55:21 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_exit(t_exec *exec, char *err_msg, int exit_code)
{
	close_all_pipes_fds(exec);
	exec_destroy(exec);
	perror(err_msg);
	exit(exit_code);
}
