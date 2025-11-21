/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:48:02 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/21 19:39:42 by pbride           ###   ########.fr       */
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
# include <sys/time.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

// === VERSION ===
# define VERSION		"V0.8"

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

# define ERR			-1

extern int	g_signal;

typedef struct s_redir
{
	int				type;
	char			*file;
	int				h_fd;
	int				tmp_fd;
	char			*tmp_file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	int				fd_in;
	int				fd_out;
	int				pipe_h[2];
	int				cmd_index;
	struct s_cmd	*next;
}	t_cmd;

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

typedef enum e_redir_status
{
	REDIR_NOT_A_REDIR = 0,
	REDIR_OK = 1,
	REDIR_ERR_SYNTAX = -1,
	REDIR_ERR_ALLOC = -2
}	t_redir_status;

typedef enum e_err_status
{
	ERR_ALLOC = -2
}	t_err_status;

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
	int		nb_cmds;
	int		fd_in;
	int		fd_out;
	int		(*pipes)[2];
	pid_t	*pids;
}	t_exec;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*content;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_shell
{
	char		**env;
	t_lexer		*lx;
	t_cmd		*cmds_head;
	t_exec		*exec;
	t_heredoc	*rdoc;
	int			last_status;
	int			running_status;
	int			stdin_backup;
	int			stdout_backup;
	int			exit_status;
}	t_shell;

// === BUILT-IN ===
int		cd(t_shell *sh, char *path, char ***env);
int		pwd(void);
int		my_env(char **envp);
int		echo(char **av);
int		my_export(char **args, char ***env);
char	*get_env_value(t_shell *sh, char **envp, char *name);
void	add_or_update_env(char ***env, const char *var_value);
int		unset(char ***env, char **args);
int		is_parent_builtin(char *cmd);
int		is_builtin(char *cmd);
int		exec_builtin(t_shell *sh, t_cmd *cmd, char ***env);
int		my_exit(void);

// === MINISHELL ===
int		main(int ac, char **av, char **envp);
void	minishell_loop(t_shell *sh);
int		init_env(t_shell *sh, char **envp);
char	*token_type_to_str(t_tokentype type);

// === TOKENISATION ===
void	skip_spaces(const char *line, int *i);
int		handle_operator(t_shell *sh, const char *line, int i);
t_token	*add_token(t_shell *sh, t_tokentype type, char *word, int is_w_malloc);
int		is_operator_char(char c);
int		tokenize_word(t_shell *sh, const char *line, int *i, char **env);
t_token	*tokenize(t_shell *sh, const char *line, char **env);
char	*extract_unquoted_part(t_shell *sh, const char *line, int *i);
char	*extract_quoted_part(t_shell *sh, const char *line, int *i);
char	*expand_vars(t_shell *sh, const char *str, int expand);
int		copy_var_value(t_shell *sh, char *dst, const char *src, int *i);
int		append_part(char **word, char *part);
int		get_part(t_shell *sh, const char *line, int *i, char **part);

// === PARSER ===
t_cmd	*parser(t_shell *sh);
int		errmsg(int special_count, t_token *line);
int		handle_specials(t_token **line);
void	append_cmd(t_cmd **head, t_cmd **last, t_cmd *cmd);
void	process_and_append(t_shell *sh, t_token **line_ptr, t_cmd **head,
			t_cmd **last);
t_cmd	*parse_all(t_shell *sh, t_token **line_ptr);

int		parse_redirections(t_token **current, t_cmd *cmd,
			int special_count, t_token *line);
int		setup_redirections(t_cmd *cmd);
t_cmd	*parse_command(t_token **current);

// === EXECUTION ===
// PIPE
void	close_all_pipes_fds(t_exec *exec);
void	create_pipes(t_shell *sh, t_exec *exec);
void	process_childs(t_shell *sh, t_exec *exec, t_cmd *cmds,
			char ***env);
void	process_parent(int cmds_index, t_exec *exec);
void	process_pipeline(t_shell *sh, t_exec *exec, t_cmd *cmds,
			char ***env);
// EXEC
void	command_not_found(char *cmd);
void	process_single_cmd(t_shell *sh, t_cmd *cmd, char ***env);
void	pipeline_exit(t_exec *exec, char *err_msg, int exit_code);
char	*resolve_cmd(char *cmd);
int		is_executable_file(char *path);
int		has_slash(char *str);
int		count_cmds(t_cmd *cmds);
int		exec_init(t_exec *exec, t_cmd *cmd);
void	wait_child(t_shell *sh, pid_t pid);
void	wait_all_childs(t_shell *sh, t_exec *exec);
void	execve_cmd(t_cmd *cmd, char ***env);
// REDIR
int		redir_apply_in(t_redir *r);
int		redir_apply_out(t_redir *r);
int		apply_append(t_redir *r);
int		handle_heredocs(t_redir *r);
/* helper: run_heredoc_child is internal to heredoc.c */
// int		run_heredoc_child(t_redir *r, int pipe_end);
int		has_heredoc(t_redir *r);

// === TEST_UTILS ===
void	assert_eq(int value, int expected, char *file, int line);
void	assert_str_eq(char *value, char *expected, char *file, int line);

// === FREE_UTILS ===
void	free_null(void *p);
void	free_tab(char **tab);
void	free_tokens(t_token *head);
void	free_cmd(t_cmd *cmd);
void	free_redirs(t_redir *redir);
void	free_exit_sh(t_shell *sh, char *mess, int code_exit);
// FREE SHELL
void	free_lx_sh(t_lexer *lx);
void	free_cmds_sh(t_cmd *cmd);
void	free_exec_sh(t_exec *exec);
void	free_rdocs_sh(t_heredoc *rdoc);

// === SIGNALS ===
void	sigint_handler(int signum);
void	sigquit_handler(int signum);
void	setup_signals(void);
void	handler_heredoc(int signum);
void	heredoc_sigint(int sig);
void	cmd_handler(int signum);

// === UTILS ===
void	print_tokens(t_lexer *lx);
void	print_cmds(t_cmd *cmd);

#endif
