/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:50:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 17:35:47 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_cmd(t_cmd **head, t_cmd **last, t_cmd *cmd)
{
	if (!*head)
	{
		*head = cmd;
		*last = cmd;
	}
	else
	{
		(*last)->next = cmd;
		*last = cmd;
	}
}
