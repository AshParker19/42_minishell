/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:05 by astein            #+#    #+#             */
/*   Updated: 2023/10/23 18:01:02 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* promt strings */
# define PROMT      "frankenshell-->  "
# define ERR_PROMT  "frankenshell: "

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
# include "builtins.h"
# include "executor.h"

/******************************************************************************/
/*    colors    */
# define GREEN 		"\033[0;32m"
# define RED 		"\033[0;31m"
# define YELLOW 	"\x1b[33m"
# define CYAN 		"\x1b[36m"
# define PURPLE 	"\x1b[35m"
# define RESET 		"\033[0m"
/******************************************************************************/
/* info for minibox */
typedef struct s_env_var t_env_var;
typedef struct s_builtin_cmd t_builtin_cmd;
// typedef struct  s_1_cycle t_1_cycle;
typedef struct s_exec t_exec;

/* 
    the main structure of the program: it is being passed as an argument to all
    the fucntions so all the data can be accesed where it needed
 */
typedef struct s_minibox
{
    // TODO: REMOVE THE VARS THAT ARE ONLY FOR ONE CYCLE!!!
    char        **env;
    t_env_var   *vars;
    
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

/* list of environment variables (definition) */
typedef struct s_env_var
{
    char        *key;
    char        *value;
    struct      s_env_var *next;
}              t_env_var;

// typedef struct  s_1_cycle 
// {
    
// }                t_1_cycle;

/******************************************************************************/

/* input_manager.c */
void	manage_input(t_minibox *minibox);

/* env.c */
void    add_var(t_minibox *minibox, char *key, char *value);    
void    load_vars(t_minibox *minibox);
char    *get_var_value(t_minibox *minibox, char *key);
void    set_var_value(t_minibox *minibox, char *key, char *value);
void    free_var(t_env_var *temp);
void    free_vars(t_minibox *minibox);
void    print_vars(t_minibox *minibox);
void    delete_var(t_minibox *minibox, char *key);
void	increment_shlvl(t_minibox *minibox);
char    **env_to_matrix(t_minibox *minibox);

/* signals.c */
void    initialize_signals();

/* manage_minibox.c */
void	initialize_box(t_minibox *minibox, char **env);
void    free_cycle(t_minibox *minibox);
// void	free_matrix(char **matrix, int i);
void    free_input_strings(t_minibox *minibox);
void    free_tokens(t_minibox *minibox);
void    free_and_close_box(t_minibox *minibox, int exit_status);

/* general_utils.c */
void    create_error_msg(const char *format, ...);

#endif