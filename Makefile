# Makefile for frankenshell

# Variables
NAME=frankenshell

# Compiler options
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
CLIBS = -L$(LIB_FOLDER) -lft -lm -lreadline
CINCLUDES  = -I$(INCLUDE_FOLDER) 
RM = rm -rf

# Colors
RED    = 	\033[0;31m
GREEN  = 	\033[0;32m
ORANGE = 	\033[0;33m
BLUE   = 	\033[34m
PURPLE = 	\033[35m
RESET  = 	\033[0m

# Folders
INCLUDE_FOLDER = ./includes/
SRC_FOLDER     = ./src/
OBJ_FOLDER     = ./obj/
LIB_FOLDER     = ./libft/

# Files
LIBFT = $(LIB_FOLDER)libft.a
SRCS = $(addprefix $(SRC_FOLDER), 						\
	1_core/0_mbox.c										\
	1_core/1_main.c										\
	1_core/2_cycle.c									\
	1_core/3_shifting.c									\
	1_core/4_env_vars.c									\
	1_core/5_signals.c									\
	1_core/6_err_msg.c									\
	2_cycle/0_mark_eq.c									\
	2_cycle/1_shift_seps.c								\
	2_cycle/2_exp_vars.c								\
	2_cycle/bb_tokenize.c								\
	2_cycle/d_parse.c									\
	2_cycle/e_execute_ast.c								\
	2_cycle/f_setup_cmd.c								\
	2_cycle/g_pipe.c									\
	2_cycle/h_fork.c									\
	2_cycle/i_redir.c									\
	2_cycle/j_hd.c										\
	2_cycle/k_hd_child.c								\
	2_cycle/k_run_cmd.c									\
	2_cycle/1_tokenizer_utils/heredoc_limiter.c			\
	2_cycle/1_tokenizer_utils/tokenizer_utils.c			\
	2_cycle/1_tokenizer_utils/tokenizer_utils2.c		\
	2_cycle/2_parser_utils/parser_utils.c				\
	2_cycle/2_parser_utils/command.c					\
	2_cycle/2_parser_utils/job.c						\
	2_cycle/2_parser_utils/redir.c						\
	2_cycle/2_parser_utils/redir_in.c					\
	2_cycle/2_parser_utils/redir_out.c					\
	2_cycle/2_parser_utils/token_list.c					\
	OLD/cmd_runner.c									\
	OLD/executor_utils.c								\
	OLD/executor_utils2.c								\
	OLD/cmd_system.c									\
	OLD/cmd_builtin.c									\
	OLD/pipes.c											\
	OLD/redirection.c									\
	3_builtins/42.c										\
	3_builtins/cd.c										\
	3_builtins/echo.c									\
	3_builtins/env.c									\
	3_builtins/exit.c									\
	3_builtins/export.c									\
	3_builtins/export_utils.c							\
	3_builtins/help.c									\
	3_builtins/history.c								\
	3_builtins/infomode.c								\
	3_builtins/pwd.c									\
	3_builtins/unset.c									\
	4_debug/info_mode.c									\
	)

# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJ_FOLDER)%.o)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

# Targets
.PHONY: all clean fclean re valgrind stats art

all:  art $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME)
	@echo "\n$(ORANGE)╔══════════════════════════╗"
	@echo "$(ORANGE)║  $(GREEN)$(NAME):  created$(ORANGE)  ║"
	@echo "$(ORANGE)╚══════════════════════════╝$(RESET)"

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c 
	@mkdir -p $(@D)
	@echo -n "$(BLUE).$(RESET)"
	@$(CC) $(CFLAGS) $(CINCLUDES)-c $< -o $@

$(LIBFT):
	@echo "$(BLUE)┌───────────────────────┐"
	@echo "│  $(ORANGE)Compiling:  libft.a$(BLUE)  │"
	@echo "$(BLUE)└───────────────────────┘$(RESET)"
	@$(MAKE) -sC $(LIB_FOLDER) DEBUG=$(DEBUG)

clean:
	@$(RM) $(OBJ_FOLDER) readline.supp
	@echo "$(PURPLE)┌───────────────────────┐"
	@echo "│     $(RED)[✓]  CLEANED!$(PURPLE)     │"
	@echo "$(PURPLE)└───────────────────────┘$(RESET)"

fclean: clean
	@make -sC $(LIB_FOLDER) fclean
	@$(RM) $(NAME)

re: fclean all

readline.supp:
	wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp

valgrind:$(NAME) readline.supp
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

stats:
	@./count_stats.sh

art:
	@./art.sh