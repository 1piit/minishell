/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:48:02 by rgalmich          #+#    #+#             */
/*   Updated: 2025/11/22 13:23:48 by rgalmich         ###   ########.fr       */
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
# include <termios.h>

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

extern volatile sig_atomic_t	g_signal;

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

typedef struct s_redir
{
	t_tokentype		type;
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
	char	*word;
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

// LOCAL HEREDOC STRUCT pour signaux
typedef struct s_hdoc_ctx
{
	pid_t			pid;
	int				fd[2];
	int				status;
	struct termios	saved_term;
	int				saved_ok;
	void			(*old_handler)(int);
}	t_hdoc_ctx;

typedef struct s_shell
{
	char			**env;
	t_lexer			*lx;
	t_cmd			*cmds_head;
	t_exec			*exec;
	t_heredoc		*rdoc;
	int				last_status;
	int				running_status;
	int				stdin_backup;
	int				stdout_backup;
	int				exit_status;
	struct termios	g_saved_term;
	char			**g_env;
}	t_shell;

// === BUILT-IN ===
int		cd(t_shell *sh, char *path, char ***env);
int		pwd(void);
int		my_env(char **envp);
int		echo(char **av);
int		my_export(char **args, char ***env);
char	*get_env_value(t_shell *sh, char **envp, char *name);
void	add_or_update_env(char ***env, const char *var_value);
void	update_env_var(char ***env, const char *var, const char *value);
int		unset(char ***env, char **args);
int		is_parent_builtin(char *cmd);
int		is_builtin(char *cmd);
int		exec_builtin(t_shell *sh, t_cmd *cmd, char ***env);
int		my_exit(t_shell *sh);

// === MINISHELL ===
int		main(int ac, char **av, char **envp);
void	minishell_loop(t_shell *sh);
int		init_env(t_shell *sh, char **envp);
char	*token_type_to_str(t_tokentype type);
void	exec_destroy(t_exec *exec);
int		create_default_env(t_shell *sh);
int		copy_envp(t_shell *sh, char **envp);
int		increment_shlvl_in_env(t_shell *sh);
t_cmd	*parse_line(t_shell *sh, char *line);
void	free_parsed_cmds(t_shell *sh);

// === TOKENISATION ===
void	skip_spaces(const char *line, int *i);
int		handle_operator(t_shell *sh, const char *line, int i);
t_token	*add_token(t_shell *sh, t_tokentype type, char *word, int is_w_malloc);
int		is_operator_char(char c);
int		tokenize_word(t_shell *sh, const char *line, int *i, char **env);
t_token	*tokenize(t_shell *sh, const char *line, char **env);
char	*extract_unquoted_part(t_shell *sh, const char *line, int *i,
			char **env);
char	*extract_quoted_part(t_shell *sh, const char *line, int *i, char **env);
char	*expand_vars(t_shell *sh, const char *str, int expand);
int		copy_var_value(t_shell *sh, char *dst, const char *src, int *i);
int		append_part(char **word, char *part);
int		get_part(t_shell *sh, const char *line, int *i, char **part);

// === PARSER ===
t_cmd	*parser(t_shell *sh);
int		errmsg(int special_count, t_token *line);
int		handle_specials(t_token **line);
void	append_cmd(t_cmd **head, t_cmd **last, t_cmd *cmd);
int		process_and_append(t_token **line_ptr, t_cmd **head,
			t_cmd **last);
t_cmd	*parse_all(t_shell *sh, t_token **line_ptr);

int		parse_redirections(t_token **current, t_cmd *cmd,
			int special_count, t_token *line);
int		setup_redirections(t_cmd *cmd);
int		process_line_sequence(t_token **line, t_cmd **head, t_cmd **last);
t_cmd	*parse_command(t_token **current);
int		count_words(t_token *tmp);
int		fill_argv(t_cmd *cmd, t_token **current);
int		handle_operator_node(t_token **line, t_cmd **head, t_cmd **last);

// === EXECUTION ===
// PIPE
void	close_all_pipes_fds(t_exec *exec);
void	create_pipes(t_exec *exec);
void	process_childs(t_shell *sh, t_exec *exec, t_cmd *cmd,
			int (*pipes)[2]);
void	child_setup_signals_and_io(t_shell *sh, t_exec *exec, t_cmd *cmd,
			int (*pipes)[2]);
void	child_close_local_pipes(int (*pipes)[2], int nb);
void	close_other_cmds_heredoc_fds(t_shell *sh, t_cmd *cmd);
void	process_parent(int cmds_index, t_exec *exec, int (*pipes)[2]);
int		process_pipeline(t_shell *sh, t_exec *exec, t_cmd *cmds);
int		spawn_and_wait(t_shell *sh, t_exec *exec, t_cmd *cmd);
// EXEC
void	command_not_found(char *cmd);
void	process_single_cmd(t_shell *sh, t_cmd *cmd, char ***env);
void	pipeline_exit(t_exec *exec, char *err_msg, int exit_code);
char	*resolve_cmd(char *cmd);
int		is_executable_file(char *path);
int		has_slash(char *str);
int		count_cmds(t_cmd *cmds);
void	exec_init(t_exec *exec, t_cmd *cmd);
void	wait_child(t_shell *sh, pid_t pid);
void	wait_all_childs(t_shell *sh, t_exec *exec);
void	execve_cmd(t_shell *sh, t_cmd *cmd, char ***env);
// REDIR
int		redir_apply_in(t_redir *r);
int		redir_apply_out(t_redir *r);
int		apply_append(t_redir *r);
int		handle_heredoc(t_shell *sh, t_redir *r);
int		handle_heredocs(t_shell *sh, t_redir *r);
int		has_heredoc(t_redir *r);

// === TEST_UTILS ===
void	assert_eq(int value, int expected, char *file, int line);
void	assert_str_eq(char *value, char *expected, char *file, int line);

// === FREE_UTILS ===
void	free_tab(char **tab);
void	free_tokens(t_token *head);
void	free_all_cmds(t_cmd *cmds);
void	free_cmd(t_cmd *cmd);
void	free_redirs(t_redir *redir);
void	free_env_tab(char **env);
void	free_lx_sh(t_lexer *lx);
void	free_cmds_sh(t_cmd *cmd);
void	free_exec_sh(t_exec *exec);
void	free_rdocs_sh(t_heredoc *rdoc);
void	free_exit_sh(t_shell *sh);
void	free_inherited_state(t_shell *sh);
void	free_and_exit(t_shell *sh, int code);
int		pre_process_single_cmd(t_shell *sh, t_cmd *cmd, char ***env);
void	close_heredoc_tmpfds(t_redir *r);
void	close_all_cmds_tmpfds(t_cmd *c);
void	free_tokens_2(t_token *head);
void	free_exit_sh_part1(t_shell *sh);
void	free_exit_sh_part2(t_shell *sh);

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
