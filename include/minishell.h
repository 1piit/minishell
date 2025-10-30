/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:48:02 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/29 20:06:45 by rgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// === NAME ===
#ifndef MINISHELL_H
# define MINISHELL_H

// === LIB ===
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

// === VERSION ===
# define VERSION		"V0.2"

// === COLOURS ===
# define NC				"\001\033[0m\002"
# define RED			"\001\033[0;31m\002"
# define CYAN			"\001\033[0;36m\002"
# define BLUE_LIGHT		"\001\033[1;34m\002"
# define GREEN			"\001\033[38;5;120m\002"
# define BLUE_DARK		"\001\033[1;38;5;33m\002"
# define PURPLE_DARK	"\001\033[38;5;93m\002"
# define PURPLE_LIGHT	"\001\033[1;35m\002"
# define WHITE			"\001\033[1;37m\002"
# define BLACK			"\001\033[30;47m\002"

extern int	g_exit_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmds;
	int		last_status;
	int		running_status;
}	t_shell;

typedef enum e_tokentype
{
	T_INVALID = 0,
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_END
}	t_tokentype;

typedef struct s_token
{
	t_tokentype		type;
	int				is_operator;
	char			*word;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token	*head;
	t_token	*last;
	char	word[4096];
	int		j;
	char	quote;
	t_cmd	*cmds;
}	t_lexer;

typedef struct s_exec
{
	int	pid;
	int	fd_in;
	int	fd_out;
	int	pipe_fd[2];
}	t_exec;

typedef struct s_expand
{
	char	*result;
	size_t	i;
	size_t	j;
}	t_expand;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*content;
	struct s_heredoc	*next;
}	t_heredoc;

// === BUILT-IN ===
int		cd(char *path);
int		pwd(void);
int		env(char **envp);
int		echo(char **av, char **alloc_env);
void	echo_print_env(char **av, int i, char **alloc_env);
void	export_no_args(char **env);
char	*get_env_value(char **env, const char *var);
void	add_or_update_env(char ***env, char *var);
void	unset(char ***env, char **args);
void	unset_var(char ***env, char *var);

// === MINISHELL ===
int		main(int ac, char **av, char **envp);
char	**init_env(char **envp);
char	*token_type_to_str(t_tokentype type);

// === TOKENISATION ===
void	skip_spaces(const char *line, int *i);
int		handle_operator(const char *line, int i, t_lexer *lx);
t_token	*add_token(t_lexer *lx, t_tokentype type, char *word);
int		is_operator_char(char c);
int		tokenize_word(const char *line, int *i, t_lexer *lx, char **env);
t_token	*tokenize(const char *line, t_lexer *lx, char **env);
char	*extract_unquoted_part(const char *line, int *i, char **env);
char	*extract_quoted_part(const char *line, int *i, char **env);
char	*expand_vars(const char *str, char **env, int expand);
int		copy_var_value(char *dst, const char *src, int *i, char **env);
int		append_part(char **word, char *part);
int		get_part(const char *line, int *i, char **part, char **env);

// PARSER
t_cmd	*parser(t_lexer *lx);
int		errmsg(int special_count, t_token *line);
void	append_cmd(t_cmd **head, t_cmd **last, t_cmd *cmd);
int		process_and_append(t_token **line_ptr, t_cmd **head,
			t_cmd **last);
t_cmd	*parse_all(t_token **line_ptr);

void	parse_redirections(t_token **current, t_cmd *cmd,
			int special_count, t_token *line);
void	setup_redirections(t_cmd *cmd);
t_cmd	*parse_command(t_token **current);

// === EXECUTION ===
void	execute_command(t_cmd *cmd);
void	execute_cmds(t_cmd *cmds);
void	redir_apply_in(t_redir *r);
void	redir_apply_out(t_redir *r);

// === TEST_UTILS ===
void	assert_eq(int value, int expected, char *file, int line);
void	assert_str_eq(char *value, char *expected, char *file, int line);

#endif
