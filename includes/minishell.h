/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:05 by astein            #+#    #+#             */
/*   Updated: 2023/10/17 15:16:10 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMT  "minihell-> "
/* system includes */
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

/* project includes */
# include "../libft/libft_printf.h"
# include "input_manager.h"
# include "executor.h"
# include "builtins.h"

/******************************************************************************/
/*    colors    */
# define GREEN 		"\033[0;32m"
# define RED 		"\033[0;31m"
# define YELLOW 	"\x1b[33m"
# define CYAN 		"\x1b[36m"
# define PURPLE 	"\x1b[35m"
# define RESET 		"\033[0m"
/******************************************************************************/
/* list of local variables */
typedef struct s_var t_var;
typedef struct s_exec t_exec;

typedef struct s_minibox
{
    char        **env;
    t_var       *vars;
    
    char        *input_original;
    char        *input_trimmed;
    char        *input_quoted;
    char        *input_expanded;
    bool        error_status;
    t_token     *tokens;
    t_token     *tmp_token;
    t_tree      *root;
    t_tree      *tmp_node;
    t_exec      executor;
}              t_minibox;

/* list of variables (definition) */
typedef struct s_var
{
    char        *key;
    char        *value;
    struct      s_var *next;
}              t_var;

/******************************************************************************/

/* input_manager.c */
void	manage_input(t_minibox *minibox);

/* env.c */
void    add_var(t_minibox *minibox, char *key, char *value);    
void    load_vars(t_minibox *minibox);
char    *get_var_value(t_minibox *minibox, char *key);
void    set_var_value(t_minibox *minibox, char *key, char *value);
void    free_var(t_var *temp);
void    free_vars(t_minibox *minibox);
void    print_vars(t_minibox *minibox);
void    delete_var(t_minibox *minibox, char *key);


/* manage_minibox.c */
void	initialize_box(t_minibox *minibox, char **env);
void    free_cycle(t_minibox *minibox);
// void	free_matrix(char **matrix, int i);
void    free_input_strings(t_minibox *minibox);
void    free_tokens(t_minibox *minibox);
void    free_and_close_box(t_minibox *minibox, int exit_status);

#endif