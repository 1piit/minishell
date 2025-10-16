# =========================
#         Minishell        
# =========================
NAME = minishell

# === DIR ===
SRC_DIR = src
OBJ_DIR = obj
MS_OBJ_DIR = $(OBJ_DIR)/minishell
LF_OBJ_DIR = $(OBJ_DIR)/libft

# === SRC/OBJ ===
#SRCS = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
SRCS = $(shell find $(SRC_DIR) -name "*.c")
LF_SRCS = $(wildcard Libft/*.c)
MS_OBJS = $(patsubst $(SRC_DIR)/%.c,$(MS_OBJ_DIR)/%.o,$(SRCS))
LF_OBJS = $(patsubst Libft/%.c,$(LF_OBJ_DIR)/%.o,$(LF_SRCS))

# === CC ===
C = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR)
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
	@$(C) $(CFLAGS) $(LF_OBJS) $(MS_OBJS) -o $(NAME) $(LDFLAGS) >/dev/null 2>&1
	@printf "$(CYAN)Compiling libft !$(NC)\n"
	@printf "$(BLUE)Compiling minishell !$(NC)\n"
	@printf "$(YELLOW)Loading: [          ]$(NC)\r"; sleep 0.2
	@printf "$(YELLOW)Loading: [█         ]$(NC)\r"; sleep 0.1
	@printf "$(BLUE)Loading: [██        ]$(NC)\r"; sleep 0.1
	@printf "$(RED)Loading: [███       ]$(NC)\r"; sleep 0.1
	@printf "$(CYAN)Loading: [████      ]$(NC)\r"; sleep 0.1
	@printf "$(RED)Loading: [█████     ]$(NC)\r"; sleep 0.1
	@printf "$(PURPLE)Loading: [██████    ]$(NC)\r"; sleep 0.1
	@printf "$(RED)Loading: [███████   ]$(NC)\r"; sleep 0.1
	@printf "$(YELLOW)Loading: [████████  ]$(NC)\r"; sleep 0.1
	@printf "$(BLUE)Loading: [█████████ ]$(NC)\r"; sleep 0.1
	@printf "$(YELLOW)Loading: [██████████]$(NC)\n"; sleep 0.2
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
	@$(C) $(CFLAGS) -c $< -o $@ >/dev/null 2>&1

$(MS_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(C) $(CFLAGS) -c $< -o $@ >/dev/null 2>&1

# ===================================================
clean:
	@printf "$(RED)Cleaning objects...$(NC)\n"
	@rm -rf $(OBJ_DIR) 2>/dev/null
	@$(MAKE) -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@sleep 0.1

# ===================================================
fclean: clean
	@printf "$(RED)Cleaning all (including $(NAME))...$(NC)\n"
	@rm -f $(NAME) 2>/dev/null
	@$(MAKE) -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	@sleep 0.1

# ===================================================
re: fclean all
