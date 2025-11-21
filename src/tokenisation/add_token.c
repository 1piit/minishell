/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:50:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 22:18:00 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_token_props(t_token *new, t_tokentype type, char *word)
{
	new->type = type;
	new->word = NULL;
	if (type != T_WORD)
		new->is_operator = 1;
	else
		new->is_operator = 0;
	if (word)
	{
		new->word = ft_strdup(word);
		if (!new->word)
			return (1);
	}
	return (0);
}

t_token	*add_token(t_shell *sh, t_tokentype type, char *word, int is_w_malloc)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		free_exit_sh(sh, "malloc", 1);
	if (set_token_props(new, type, word) != 0)
	{
		free_null((void **)&new);
		if (is_w_malloc)
			free_null((void **)&word);
		free_exit_sh(sh, "malloc", 1);
	}
	new->next = NULL;
	if (sh->lx->head == NULL)
		sh->lx->head = new;
	else
		(sh->lx->last)->next = new;
	sh->lx->last = new;
	return (new);
}
