# Makefile for minishell
#.SILENT:

# Variables
NAME=minishell 

# Prints DEBUG Messages
DEBUG = 0

# Compiler options
CC = cc
CFLAGS = -D DEBUG=$(DEBUG) -Wall -Werror -Wextra #-g -fsanitize=address -fsanitize-address-use-after-scope
CLIBS = -L$(LIB_FOLDER) -lft_printf -lm
CINCLUDES  = -I$(INCLUDE_FOLDER) 
RM = rm -f

# Color codes
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m

# ->Folders
INCLUDE_FOLDER = ./include/
LIB_FOLDER = ./lib/

# ->Files
LIBFT_PRINTF = $(LIB_FOLDER)libft_printf.a
SRCS= \
	main.c
	
# Object files
OBJS= $(SRCS:.c=.o)

# TARGETS
.PHONY: all clean fclean re norm god

all: $(NAME)

$(NAME): $(LIBFT_PRINTF) $(OBJS) 
	$(CC) $(OBJS) $(CFLAGS) $(CLIBS) $(CINCLUDES) -o $(NAME)
	echo "$(GREEN)$(NAME): created$(RESET)"

$(LIBFT_PRINTF):
	echo "$(ORANGE)compiling: $(LIBFT_PRINTF)\n$(RESET)"
	$(MAKE) --no-print-directory -C $(LIB_FOLDER) DEBUG=$(DEBUG)

clean:
	$(RM) $(OBJS_SERVER)
	echo "$(RED)$(NAME_SERVER): cleaned object files$(RESET)"
	$(RM) $(OBJS_CLIENT)
	echo "$(RED)$(NAME_CLIENT): cleaned object files$(RESET)"

fclean: clean
	make --no-print-directory -C $(LIB_FOLDER) fclean
	$(RM) $(NAME_SERVER)
	echo "$(RED)$(NAME_SERVER): cleaned program$(RESET)"
	$(RM) $(NAME_CLIENT)
	echo "$(RED)$(NAME_CLIENT): cleaned program$(RESET)"

re: fclean all

test: all
	gnome-terminal --window --hide-menubar --title "ASTEINS MINITALK TESTER" --geometry=60x10+630+100 --working-directory="$(CURDIR)$(TEST_FOLDER)" -- "./run.sh" &

norm:
	norminette

a: fclean
	git add .
	git commit -m 'Makefile - ALEX'
	git status

t: fclean
	git add .
	git commit -m 'Makefile - ANATOLII'
	git status

git_sync_a:
	git checkout alex
	git fetch origin
	git checkout main
	git pull origin main
	git checkout alex
	git merge main
	git checkout alex
	git push origin main
	git status

git_sync_t:
	git checkout anatolii
	git fetch origin
	git checkout main
	git pull origin main
	git checkout anatolii
	git merge main
	git checkout anatolii
	git push origin main
	git status
