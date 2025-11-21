/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:10:24 by pbride            #+#    #+#             */
/*   Updated: 2025/11/21 20:49:01 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_destroy(t_exec *exec)
{
	free(exec->pipes);
	free(exec->pids);
}


void	print_tokens(t_lexer *lx)
{
	t_lexer	*p_lx;
	t_token	*p_tok;

	printf("=== Print tokens ===\n");
	p_lx = lx;
	p_tok = p_lx->head;
	while (p_tok)
	{
		printf("Token: %s, %d, %d\n",
			p_tok->word, p_tok->type, p_tok->is_operator);
		p_tok = p_tok->next;
	}
}

void	print_cmds(t_cmd *cmd)
{
	t_cmd	*p_cmd;
	int		arg_i;

	printf("=== Print cmds ===\n");
	p_cmd = cmd;
	while (p_cmd)
	{
		arg_i = 0;
		while (p_cmd->argv[arg_i])
		{
			printf("Argv: %s, ", p_cmd->argv[arg_i]);
			arg_i++;
		}
		printf("\n");
		while (p_cmd->redir)
		{
			printf("Redir: type=%d, file=%s\n",
				p_cmd->redir->type, p_cmd->redir->file);
			p_cmd->redir = p_cmd->redir->next;
		}
		printf("fd_in=%d fd_out=%d\n", p_cmd->fd_in, p_cmd->fd_out);
		p_cmd = p_cmd->next;
	}
}
