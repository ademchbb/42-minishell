# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/10 10:14:34 by adchebbi          #+#    #+#              #
#    Updated: 2026/07/03 21:03:45 by adchebbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

INC_DIR     = inc/
SRCS_DIR    = srcs/
LIBFT_DIR   = libft/
OBJ_DIR     = obj/

SRCS        = $(SRCS_DIR)/lexer/lexer.c \
			  $(SRCS_DIR)/lexer/quote_removal.c \
			  $(SRCS_DIR)/env/env.c \
			  $(SRCS_DIR)/env/env_utils.c \
			  $(SRCS_DIR)/main/main.c \
              $(SRCS_DIR)/parser/parser.c \
              $(SRCS_DIR)/parser/parser_utils.c \
              $(SRCS_DIR)/parser/syntax_check.c \
              $(SRCS_DIR)/parser/parser_free.c \
              $(SRCS_DIR)/utils/error.c \
              $(SRCS_DIR)/utils/ms_split.c \
              $(SRCS_DIR)/utils/add_spaces.c \
			  $(SRCS_DIR)/exec/env_array.c \
			  $(SRCS_DIR)/exec/exec_child.c \
			  $(SRCS_DIR)/exec/exec_path.c \
			  $(SRCS_DIR)/exec/exec_redirs.c \
			  $(SRCS_DIR)/exec/exec.c \
			  $(SRCS_DIR)/exec/heredoc_utils.c \
			  $(SRCS_DIR)/exec/heredoc.c \
			  $(SRCS_DIR)/expander/expander_utils.c \
			  $(SRCS_DIR)/expander/expander.c \
			  $(SRCS_DIR)/signals/signals.c \
			  $(SRCS_DIR)/signals/heredoc_signals.c \
			  $(SRCS_DIR)/builtins/built_ins.c \
			  $(SRCS_DIR)/builtins/env_ops.c \
			  $(SRCS_DIR)/builtins/built_in_echo.c \
			  $(SRCS_DIR)/builtins/built_in_pwd.c \
			  $(SRCS_DIR)/builtins/built_in_env.c \
			  $(SRCS_DIR)/builtins/built_in_cd.c \
			  $(SRCS_DIR)/builtins/built_in_export.c \
			  $(SRCS_DIR)/builtins/built_in_export_print.c \
			  $(SRCS_DIR)/builtins/built_in_unset.c \
			  $(SRCS_DIR)/builtins/built_in_exit.c \

OBJS        = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

LIBFT       = $(LIBFT_DIR)libft.a

GREEN       = \033[1;32m
RED         = \033[1;31m
RESET       = \033[0m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)[#] Exécutable '$(NAME)' créé avec succès !$(RESET)"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	@echo "Compilation de la libft..."
	@make -C $(LIBFT_DIR) --no-print-directory

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(RED)[-] Dossier $(OBJ_DIR) supprimé.$(RESET)"
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RED)[-] Exécutable '$(NAME)' et libft.a supprimés.$(RESET)"
	@sleep 1
	@clear

re: fclean all

.PHONY: all clean fclean re