/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 17:50:00 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 21:40:06 by rgalmich         ###   ########.fr       */
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
		return (NULL);
	if (set_token_props(new, type, word) != 0)
	{
		if (is_w_malloc)
			free(word);
		free(new);
		printf("fonction: exit_all + free_all");
		return (NULL);
	}
	new->next = NULL;
	if (sh->lx->head == NULL)
		sh->lx->head = new;
	else
		(sh->lx->last)->next = new;
	sh->lx->last = new;
	return (new);
}
