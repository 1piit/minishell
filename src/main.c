/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/10/27 12:47:08 by rgalmich         ###   ########.fr       */
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
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		printf(RED "Type: %s, Word: [%s]\n\n" NC,
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
		printf("=====TOKENISATION=====\n");
		print_tokens(tokens);
		printf("=====PARSING=====\n");
		parser(&lx);
		printf("=====EXEC=====\n");
		free(line);
	}
	return (0);
}

