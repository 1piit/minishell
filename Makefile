# =========================
#         Minishell
# =========================
NAME = minishell

# === DIR ===
SRC_DIR = src
MS_OBJ_DIR = obj
LF_OBJ_DIR = obj/libft

MS_SRCS = \
	src/main.c \
	src/minishell.c \
	src/built_in/cd.c \
	src/built_in/echo.c \
	src/built_in/env.c \
	src/built_in/exit.c \
	src/built_in/export.c \
	src/built_in/is_builtin.c \
	src/built_in/pwd.c \
	src/built_in/unset.c \
	src/execution/exec.c \
	src/execution/exec_child.c \
	src/execution/exec_exit.c \
	src/execution/exec_helpers.c \
	src/execution/exec_manage_errors.c \
	src/execution/exec_utils.c \
	src/execution/heredoc.c \
	src/execution/heredoc_setup.c \
	src/execution/heredocs_setup.c \
	src/execution/heredoc_utils.c \
	src/execution/pipeline.c \
	src/execution/pipeline_helpers.c \
	src/execution/pipeline_spawn.c \
	src/execution/pipeline_utils.c \
	src/execution/redir.c \
	src/free_utils/ft_free.c \
	src/free_utils/ft_free_exit_shell.c \
	src/free_utils/ft_free_exit_shell_parts.c \
	src/free_utils/utils2.c \
	src/init/copy_envp.c \
	src/init/env_helpers.c \
	src/init/init_env.c \
	src/parse_utils/line_utils.c \
	src/parsing/errmsg.c \
	src/parsing/parse_redir.c \
	src/parsing/parse_utils.c \
	src/parsing/parsing.c \
	src/parsing/parsing_utils.c \
	src/print_utils/utils.c \
	src/signals.c \
	src/tokenisation/add_token.c \
	src/tokenisation/expand.c \
	src/tokenisation/tokenisation.c \
	src/tokenisation/tokenisation_utils.c \
	src/tokenisation/token_type_to_str.c

LF_SRCS = \
	Libft/ft_atoi.c \
	Libft/ft_bzero.c \
	Libft/ft_calloc.c \
	Libft/ft_isalnum.c \
	Libft/ft_isalpha.c \
	Libft/ft_isascii.c \
	Libft/ft_isdigit.c \
	Libft/ft_isprint.c \
	Libft/ft_itoa.c \
	Libft/ft_lstadd_back_bonus.c \
	Libft/ft_lstadd_front_bonus.c \
	Libft/ft_lstclear_bonus.c \
	Libft/ft_lstdelone_bonus.c \
	Libft/ft_lstiter_bonus.c \
	Libft/ft_lstlast_bonus.c \
	Libft/ft_lstmap_bonus.c \
	Libft/ft_lstnew_bonus.c \
	Libft/ft_lstsize_bonus.c \
	Libft/ft_memchr.c \
	Libft/ft_memcmp.c \
	Libft/ft_memcpy.c \
	Libft/ft_memmove.c \
	Libft/ft_memset.c \
	Libft/ft_putchar_fd.c \
	Libft/ft_putendl_fd.c \
	Libft/ft_putnbr_fd.c \
	Libft/ft_putstr_fd.c \
	Libft/ft_split.c \
	Libft/ft_strchr.c \
	Libft/ft_strcmp.c \
	Libft/ft_strcpy.c \
	Libft/ft_strdup.c \
	Libft/ft_striteri.c \
	Libft/ft_strjoin.c \
	Libft/ft_strlcat.c \
	Libft/ft_strlcpy.c \
	Libft/ft_strlen.c \
	Libft/ft_strmapi.c \
	Libft/ft_strncmp.c \
	Libft/ft_strnstr.c \
	Libft/ft_strrchr.c \
	Libft/ft_strtrim.c \
	Libft/ft_substr.c \
	Libft/ft_tolower.c \
	Libft/ft_toupper.c

MS_OBJS = \
	obj/main.o \
	obj/minishell.o \
	obj/built_in/cd.o \
	obj/built_in/echo.o \
	obj/built_in/env.o \
	obj/built_in/exit.o \
	obj/built_in/export.o \
	obj/built_in/is_builtin.o \
	obj/built_in/pwd.o \
	obj/built_in/unset.o \
	obj/execution/exec.o \
	obj/execution/exec_child.o \
	obj/execution/exec_exit.o \
	obj/execution/exec_helpers.o \
	obj/execution/exec_manage_errors.o \
	obj/execution/exec_utils.o \
	obj/execution/heredoc.o \
	obj/execution/heredoc_setup.o \
	obj/execution/heredocs_setup.o \
	obj/execution/heredoc_utils.o \
	obj/execution/pipeline.o \
	obj/execution/pipeline_helpers.o \
	obj/execution/pipeline_spawn.o \
	obj/execution/pipeline_utils.o \
	obj/execution/redir.o \
	obj/free_utils/ft_free.o \
	obj/free_utils/ft_free_exit_shell.o \
	obj/free_utils/ft_free_exit_shell_parts.o \
	obj/free_utils/utils2.o \
	obj/init/copy_envp.o \
	obj/init/env_helpers.o \
	obj/init/init_env.o \
	obj/parse_utils/line_utils.o \
	obj/parsing/errmsg.o \
	obj/parsing/parse_redir.o \
	obj/parsing/parse_utils.o \
	obj/parsing/parsing.o \
	obj/parsing/parsing_utils.o \
	obj/print_utils/utils.o \
	obj/signals.o \
	obj/tokenisation/add_token.o \
	obj/tokenisation/expand.o \
	obj/tokenisation/tokenisation.o \
	obj/tokenisation/tokenisation_utils.o \
	obj/tokenisation/token_type_to_str.o

LF_OBJS = \
	obj/libft/ft_atoi.o \
	obj/libft/ft_bzero.o \
	obj/libft/ft_calloc.o \
	obj/libft/ft_isalnum.o \
	obj/libft/ft_isalpha.o \
	obj/libft/ft_isascii.o \
	obj/libft/ft_isdigit.o \
	obj/libft/ft_isprint.o \
	obj/libft/ft_itoa.o \
	obj/libft/ft_lstadd_back_bonus.o \
	obj/libft/ft_lstadd_front_bonus.o \
	obj/libft/ft_lstclear_bonus.o \
	obj/libft/ft_lstdelone_bonus.o \
	obj/libft/ft_lstiter_bonus.o \
	obj/libft/ft_lstlast_bonus.o \
	obj/libft/ft_lstmap_bonus.o \
	obj/libft/ft_lstnew_bonus.o \
	obj/libft/ft_lstsize_bonus.o \
	obj/libft/ft_memchr.o \
	obj/libft/ft_memcmp.o \
	obj/libft/ft_memcpy.o \
	obj/libft/ft_memmove.o \
	obj/libft/ft_memset.o \
	obj/libft/ft_putchar_fd.o \
	obj/libft/ft_putendl_fd.o \
	obj/libft/ft_putnbr_fd.o \
	obj/libft/ft_putstr_fd.o \
	obj/libft/ft_split.o \
	obj/libft/ft_strchr.o \
	obj/libft/ft_strcmp.o \
	obj/libft/ft_strcpy.o \
	obj/libft/ft_strdup.o \
	obj/libft/ft_striteri.o \
	obj/libft/ft_strjoin.o \
	obj/libft/ft_strlcat.o \
	obj/libft/ft_strlcpy.o \
	obj/libft/ft_strlen.o \
	obj/libft/ft_strmapi.o \
	obj/libft/ft_strncmp.o \
	obj/libft/ft_strnstr.o \
	obj/libft/ft_strrchr.o \
	obj/libft/ft_strtrim.o \
	obj/libft/ft_substr.o \
	obj/libft/ft_tolower.o \
	obj/libft/ft_toupper.o

# === CC ===
C = cc
CFLAGS = -Wall -Wextra -Werror -g3 -Iinclude -I$(LIBFT_DIR)
LDFLAGS = -lreadline

# === LIBFT ===
LIBFT_DIR = Libft

# === COLOURS ===
GREEN    = \033[0;32m
BLUE     = \033[0;34m
YELLOW   = \033[0;33m
RED      = \033[0;31m
NC       = \033[0m
CYAN     = \033[0;36m
PURPLE   = \033[0;35m

.PHONY: all clean fclean re

# ===================================================
all: $(NAME)

# ===================================================
$(NAME): $(MS_OBJS) $(LF_OBJS)
	@printf "$(YELLOW)Starting $(NAME) !$(NC)\n"
	@$(C) $(CFLAGS) $(LF_OBJS) $(MS_OBJS) -o $(NAME) $(LDFLAGS)
	@printf "$(CYAN)Compiling libft !$(NC)\n"
	@printf "$(BLUE)Compiling minishell !$(NC)\n"
	@printf "$(GREEN)✔ Compilation terminée ! $(NAME) est prêt.$(NC)\n\n"
	@printf "$(PURPLE)\
MMMMMMMM               MMMMMMMM  iiii                     iiii                  hhhhhhh                                lllllll lllllll \n\
M:::::::M             M:::::::M i::::i                   i::::i                 h:::::h                                l:::::l l:::::l \n\
M::::::::M           M::::::::M  iiii                     iiii                  h:::::h                                l:::::l l:::::l \n\
M:::::::::M         M:::::::::M                                                 h:::::h                                l:::::l l:::::l \n\
M::::::::::M       M::::::::::Miiiiiiinnnn  nnnnnnnn    iiiiiii     ssssssssss   h::::h hhhhh           eeeeeeeeeeee    l::::l  l::::l \n\
M:::::::::::M     M:::::::::::Mi:::::in:::nn::::::::nn  i:::::i   ss::::::::::s  h::::hh:::::hhh      ee::::::::::::ee  l::::l  l::::l \n\
M:::::::M::::M   M::::M:::::::M i::::in::::::::::::::nn  i::::i ss:::::::::::::s h::::::::::::::hh   e::::::eeeee:::::eel::::l  l::::l \n\
M::::::M M::::M M::::M M::::::M i::::inn:::::::::::::::n i::::i s::::::ssss:::::sh:::::::hhh::::::h e::::::e     e:::::el::::l  l::::l \n\
M::::::M  M::::M::::M  M::::::M i::::i  n:::::nnnn:::::n i::::i  s:::::s  ssssss h::::::h   h::::::he:::::::eeeee::::::el::::l  l::::l \n\
M::::::M   M:::::::M   M::::::M i::::i  n::::n    n::::n i::::i    s::::::s      h:::::h     h:::::he:::::::::::::::::e l::::l  l::::l \n\
M::::::M    M:::::M    M::::::M i::::i  n::::n    n::::n i::::i       s::::::s   h:::::h     h:::::he::::::eeeeeeeeeee  l::::l  l::::l \n\
M::::::M     MMMMM     M::::::M i::::i  n::::n    n::::n i::::i ssssss   s:::::s h:::::h     h:::::he:::::::e           l::::l  l::::l \n\
M::::::M               M::::::Mi::::::i n::::n    n::::ni::::::is:::::ssss::::::sh:::::h     h:::::he::::::::e         l::::::ll::::::l\n\
M::::::M               M::::::Mi::::::i n::::n    n::::ni::::::is::::::::::::::s h:::::h     h:::::h e::::::::eeeeeeee l::::::ll::::::l\n\
M::::::M               M::::::Mi::::::i n::::n    n::::ni::::::i s:::::::::::ss  h:::::h     h:::::h  ee:::::::::::::e l::::::ll::::::l\n\
MMMMMMMM               MMMMMMMMiiiiiiii nnnnnn    nnnnnniiiiiiii  sssssssssss    hhhhhhh     hhhhhhh    eeeeeeeeeeeeee llllllllllllllll\n\
                                                                                                                                        \n$(NC)"

# ===================================================
$(LF_OBJ_DIR)/%.o: Libft/%.c
	@mkdir -p $(LF_OBJ_DIR)
	@$(C) $(CFLAGS) -c $< -o $@

$(MS_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(C) $(CFLAGS) -c $< -o $@

# ===================================================
clean:
	@printf "$(RED)Cleaning objects...$(NC)\n"
	@rm -rf $(OBJ_DIR) 2>/dev/null
	@$(MAKE) -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@sleep 0.1

# ===================================================
fclean: clean
	@printf "$(RED)Cleaning all (including $(NAME) $(TEST_EXEC))...$(NC)\n"
	@rm -f $(NAME) 2>/dev/null
	@rm -f $(TEST_EXEC) 2>/dev/null
	@$(MAKE) -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	@sleep 0.1

# ===================================================
re: fclean all

tags: ${SRCS}
	ctags ${SRCS}

v: tags
	vim ${SRCS} minishell.h Makefile

supp.supp:
	echo "{\nignore_libreadline_leaks\nMemcheck:Leak\n...\nobj:*/libreadline.so.*\n}" > supp.supp

val: supp.supp ${NAME}
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --show-reachable=yes --track-origins=yes --trace-children=yes --track-fds=yes --undef-value-errors=yes ./minishell
