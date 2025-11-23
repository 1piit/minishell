/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 06:30:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/23 16:18:56 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_line(t_shell *sh, char *line)
{
	t_cmd	*cmds;

	sh->lx = ft_calloc(1, sizeof(t_lexer));
	if (!sh->lx)
		return (free_exit_sh(sh), NULL);
	tokenize(sh, line, sh->env);
	cmds = parser(sh);
	if (sh->lx && sh->lx->head)
	{
		free_tokens_2(sh->lx->head);
		sh->lx->head = NULL;
	}
	if (!cmds)
	{
		if (sh->lx && sh->lx->word)
			free(sh->lx->word);
		free(sh->lx);
		sh->lx = NULL;
		return (NULL);
	}
	sh->lx->cmds = cmds;
	return (cmds);
}

void	free_parsed_cmds(t_shell *sh)
{
	t_cmd	*cmds;
	t_cmd	*next;

	if (!sh->lx)
		return ;
	cmds = sh->lx->cmds;
	while (cmds)
	{
		next = cmds->next;
		free_cmd(cmds);
		cmds = next;
	}
	sh->lx->cmds = NULL;
	if (sh->lx->word)
		free(sh->lx->word);
	free_lx_sh(sh->lx);
	sh->lx = NULL;
}
