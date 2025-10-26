/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:21:11 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/24 14:53:46 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour afficher la liste de tokens
void	print_tokens(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("Type: %s, Word: [%s]\n",
			token_type_to_str(tmp->type), tmp->word ? tmp->word : "(null)");
		tmp = tmp->next;
	}
}

// Exemple d’utilisation
int	main(void)
{
	t_lexer	lx;
	char	*line;
	t_token	*tokens;

	lx.head = NULL;
	lx.last = NULL;
	line = readline("minishell $ ");
	if (!line)
		return (perror("Error: "), 1);
	tokens = tokenize(line, &lx);
	if (!tokens)
		return (printf("Erreur de tokenization\n"), 1);
	parser(&lx);
	//print_tokens(tokens);

	return (0);
}
