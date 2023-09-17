# Makefile for minishell
# .SILENT:

# Variables
NAME=minishell

# Prints DEBUG Messages
DEBUG = 0

# Compiler options
CC = cc
CFLAGS = -D DEBUG=$(DEBUG) -Wall -Werror -Wextra #-g -fsanitize=address -fsanitize-address-use-after-scope
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
SRCS = $(addprefix $(SRC_FOLDER), \
	main.c \
	parser.c \
	bultin_echo.c\
	bultin_cd.c\
	bultin_pwd.c\
	bultin_export.c\
	bultin_unset.c\
	bultin_env.c\
	bulitin_exit.c\
	signals.c\
	parsing/parsing1.c)
	
# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJ_FOLDER)%.o)

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

# TARGETS
.PHONY: all clean fclean re norm

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	@$(CC) $(OBJS) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME)
	@echo "$(GREEN)$(NAME): created$(RESET)"

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c
	@mkdir -p $(@D)
	@echo -n "$(ORANGE).$(RESET)"
	@$(CC) $(CFLAGS) $(CINCLUDES)-c $< -o $@

$(LIBFT):
	@echo "$(ORANGE)compiling: $(LIBFT)\n$(RESET)"
	@$(MAKE) -sC $(LIB_FOLDER) DEBUG=$(DEBUG)

clean:
	@$(RM) $(OBJ_FOLDER)
	@echo "$(BLUE)┌────────────────────┐"
	@echo "│    $(ORANGE)[✓] CLEANED!$(BLUE)    │"
	@echo "$(BLUE)└────────────────────┘$(RESET)"

fclean: clean
	@make -sC $(LIB_FOLDER) fclean
	@$(RM) $(NAME)

re: fclean all

test: all
	gnome-terminal --window --hide-menubar --title "ASTEINS MINITALK TESTER" --geometry=60x10+630+100 --working-directory="$(CURDIR)$(TEST_FOLDER)" -- "./run.sh" &

norm:
	norminette

