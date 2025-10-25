/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:21:11 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/25 18:27:49 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;
/*
if (exec_failed)
	g_exit_status = 127;
else
	g_exit_status = WEXITSTATUS(status);
*/
// Fonction pour afficher la liste de tokens

void	print_tokens(t_token *head)
{
	t_token *tmp = head;

	while (tmp)
	{
		printf("Type: %s, Word: [%s]\n",
			token_type_to_str(tmp->type), tmp->word ? tmp->word : "(null)");
		tmp = tmp->next;
	}
}

// Exemple d’utilisation
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_lexer lx;
    char *line;
    t_token *tokens;
    char **env;

	env = init_env(envp);
	while (1)
	{
		lx.head = NULL;
		lx.last = NULL;
		line = readline("minishell $ ");
		if (!line)
		{
			printf("\n");
			break ;
		}
		if (*line)
			add_history(line);
		tokens = tokenize(line, &lx, env);
		if (!tokens)
		{
			printf("Erreur de tokenization\n");
			free(line);
			continue ;
		}
		print_tokens(tokens);
		free(line);
	}
	return (0);
}

