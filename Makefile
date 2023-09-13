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
RM = rm -f

# Color codes
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m

# ->Folders
INCLUDE_FOLDER = ./include/
SRC_FOLDER = ./src/
OBJ_FOLDER = ./obj/
LIB_FOLDER = ./lib/

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
	signals.c)
	
# Object files
OBJS = $(SRCS:$(SRC_FOLDER)%.c=$(OBJ_FOLDER)%.o)

# TARGETS
.PHONY: all clean fclean re norm

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	$(CC) $(OBJS) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME)
	echo "$(GREEN)$(NAME): created$(RESET)"

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c
	mkdir -p $(@D)
	echo -n "$(ORANGE).$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	echo "$(ORANGE)compiling: $(LIBFT)\n$(RESET)"
	$(MAKE) --no-print-directory -C $(LIB_FOLDER) DEBUG=$(DEBUG)

clean:
	$(RM) $(OBJS)
	echo "$(RED)$(NAME): cleaned object files$(RESET)"

fclean: clean
	make --no-print-directory -C $(LIB_FOLDER) fclean
	$(RM) $(NAME)
	echo "$(RED)$(NAME): cleaned program$(RESET)"

re: fclean all

test: all
	gnome-terminal --window --hide-menubar --title "ASTEINS MINITALK TESTER" --geometry=60x10+630+100 --working-directory="$(CURDIR)$(TEST_FOLDER)" -- "./run.sh" &

norm:
	norminette

