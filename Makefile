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
	1_core/7_utils.c									\
	1_core/8_info_mode.c								\
	2_cycle/0_mark_eq.c									\
	2_cycle/1_shift_seps.c								\
	2_cycle/2_exp_vars.c								\
	2_cycle/3_tokenize.c								\
	2_cycle/4_parse.c									\
	2_cycle/5_execute_ast.c								\
	2_cycle/f_setup_cmd.c								\
	2_cycle/g_pipe.c									\
	2_cycle/h_fork.c									\
	2_cycle/i_redir.c									\
	2_cycle/j_hd.c										\
	2_cycle/k_hd_child.c								\
	2_cycle/k_run_cmd.c									\
	3_parser/1_job.c									\
	3_parser/2_command.c								\
	3_parser/3_token_list.c								\
	3_parser/4_redir.c									\
	3_parser/5_redir_in.c								\
	3_parser/6_redir_out.c								\
	OLD/cmd_runner.c									\
	OLD/executor_utils.c								\
	OLD/executor_utils2.c								\
	OLD/cmd_system.c									\
	OLD/pipes.c											\
	OLD/redirection.c									\
	4_builtins/0_builtins_utils.c						\
	4_builtins/42.c										\
	4_builtins/cd.c										\
	4_builtins/echo.c									\
	4_builtins/env.c									\
	4_builtins/exit.c									\
	4_builtins/export.c									\
	4_builtins/export_utils.c							\
	4_builtins/help.c									\
	4_builtins/history.c								\
	4_builtins/infomode.c								\
	4_builtins/pwd.c									\
	4_builtins/unset.c									\
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