/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:08:24 by pbride            #+#    #+#             */
/*   Updated: 2025/11/07 00:11:21 by pbride           ###   ########.fr       */
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
