/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:40:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/10 17:15:28 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_command(t_token **current)
{
	t_cmd	*cmd;
	int		argc;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *) * 1024);
	if (!cmd->argv)
		return (free(cmd), NULL);
	cmd->redir = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->next = NULL;
	argc = 0;
	while (*current && (*current)->type == T_WORD)
	{
		cmd->argv[argc] = ft_strdup((*current)->word);
		argc++;
		*current = (*current)->next;
	}
	cmd->argv[argc] = NULL;
	return (cmd);
}
