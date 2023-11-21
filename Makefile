# Makefile for minishell
# .SILENT:

# Variables
NAME=minishell

# Prints DEBUG Messages
DEBUG = 0

# Compiler options
CC = cc
CFLAGS = -D DEBUG=$(DEBUG) -g #-Wall -Werror -Wextra  #-gp -fsanitize=address -fsanitize-address-use-after-scope
CLIBS = -L$(LIB_FOLDER) -lft -lm -lreadline
CINCLUDES  = -I$(INCLUDE_FOLDER) 
RM = rm -rf

# ->Colors
RED    = 	\033[0;31m
GREEN  = 	\033[0;32m
ORANGE = 	\033[0;33m
BLUE   = 	\033[34m
PURPLE = 	\033[35m
RESET  = 	\033[0m

# ->Folders
INCLUDE_FOLDER = ./includes/
SRC_FOLDER     = ./src/
OBJ_FOLDER     = ./obj/
LIB_FOLDER     = ./libft/

# ->Files
LIBFT = $(LIB_FOLDER)libft.a
SRCS = $(addprefix $(SRC_FOLDER), 						\
	0_core/main.c										\
	0_core/environment.c								\
	0_core/env_utils.c									\
	0_core/env_utils2.c									\
	0_core/general_utils.c								\
	0_core/input_manager.c								\
	0_core/manage_mbox.c								\
	0_core/signals.c									\
	0_core/display_flow.c								\
	0_core/display_flow2.c								\
	1_input_manager/1_0_tokenizer/expand_vars.c			\
	1_input_manager/1_0_tokenizer/tokenizer.c 			\
	1_input_manager/1_0_tokenizer/tokenizer_utils.c		\
	1_input_manager/1_0_tokenizer/tokenizer_utils2.c	\
	1_input_manager/1_0_tokenizer/shifter.c				\
	1_input_manager/1_0_tokenizer/heredoc_limiter.c		\
	1_input_manager/1_1_parser/parser.c					\
	1_input_manager/1_1_parser/job.c					\
	1_input_manager/1_1_parser/command.c				\
	1_input_manager/1_1_parser/token_list.c				\
	1_input_manager/1_1_parser/redir.c					\
	1_input_manager/1_1_parser/redir_in.c				\
	1_input_manager/1_1_parser/redir_out.c				\
	1_input_manager/1_1_parser/parser_utils.c			\
	2_executor/executor.c								\
	2_executor/cmd_runner.c								\
	2_executor/executor_utils.c							\
	2_executor/cmd_system.c								\
	2_executor/cmd_builtin.c							\
	2_executor/pipes.c									\
	2_executor/redirection.c							\
	2_executor/heredoc.c								\
	2_executor/heredoc_utils.c							\
	2_executor/heredoc_utils2.c							\
	3_builtins/cd.c										\
	3_builtins/echo.c									\
	3_builtins/pwd.c									\
	3_builtins/export.c									\
	3_builtins/unset.c									\
	3_builtins/env.c									\
	3_builtins/exit.c									\
	3_builtins/history.c								\
	3_builtins/header.c									\
	)

# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJ_FOLDER)%.o)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

# TARGETS
.PHONY: all clean fclean re norm

all:  $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME)
	@echo "\n$(ORANGE)╔═══════════════════════╗"
	@echo "$(ORANGE)║  $(GREEN)$(NAME):  created$(ORANGE)  ║" #revived
	@echo "$(ORANGE)╚═══════════════════════╝$(RESET)"

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

norm:
	norminette

line:
	norminette | grep "TOO_MANY_LINES"

readline.supp:
	wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp

valmem:$(NAME) readline.supp
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./$(NAME)

valfd:$(NAME) readline.supp
	valgrind --track-fds=yes --suppressions=readline.supp ./$(NAME)

valchild:$(NAME) readline.supp
	valgrind --trace-children=yes --suppressions=readline.supp ./$(NAME)

valgrind:$(NAME) readline.supp
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

HEADER_PRINT:
	@echo "$(ORANGE)┌───────────────────────┐"
	@echo "│ $(BLUE)Compiling:  $(NAME)$(ORANGE) │"
	@echo "$(ORANGE)└───────────────────────┘$(RESET)"

DOT:
	gprof minishell
	gprof ./minishell | /nfs/homes/astein/Downloads/gprof2dot/gprof2dot.py | xclip -selection clipboard
	echo "DONE - NOW IS IN CLIPBOARD"

stats:
	./tester/count_stats.sh

t: t1 t2

t1: all
	$(call print_header, "https://github.com/MariaAguiar/minitester")
	@cp ./minishell ./tester/minishell
	@cd ./tester/tester1 && bash ./minitester.sh

t2: all
	$(call print_header, "https://github.com/LucasKuhn/minishell_tester")
	@cp ./minishell ./tester/minishell
	$(call print_header, NORMAL)
	@cd ./tester/tester2 && bash ./tester || echo "TEST COMPLETED"
	$(call print_header, SYNTAX)
	@cd ./tester/tester2 && bash ./tester syntax || echo "TEST COMPLETED"
	$(call print_header, OS SPECIFIC)
	@cd ./tester/tester2 && bash ./tester os_specific || echo "TEST COMPLETED"
	$(call print_header, FRANKENSHELL TEST)
	@cd ./tester/tester2 && bash ./tester ./frankenshell/tests || echo "TEST COMPLETED"

run: all
	./minishell