/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalmich <rgalmich@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:48:02 by rgalmich          #+#    #+#             */
/*   Updated: 2025/10/01 13:48:03 by rgalmich         ###   ########.fr       */
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

#endif