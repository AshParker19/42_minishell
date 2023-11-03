/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:05 by astein            #+#    #+#             */
/*   Updated: 2023/11/03 16:50:17 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* promt strings */
# define PROMT      "\x1b[36mfrankenshell-->\033[0m "
# define ERR_PROMT  "frankenshell: "

# define FRANKENSHELL_RISES_AMIDTS_DEATH 1

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

//TODO: cerror checking FIXME: don't forget to remove at the end
// # define malloc(x) NULL
// # define fork() -1
// # define pipe(x) -1
// # define dup2(x, y) -1 //TODO: make protections for other fucntion which can break
 //!TODO: !!!IMPORTANT!!!  when we exit in these cases, we don't care about the exit status, it's always 0

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
/* info for mbox */
typedef struct s_env_var t_env_var;
typedef struct s_builtin_cmd t_builtin_cmd;
typedef struct s_exec t_exec;

enum e_signal_state
{
    SIGNAL_MAIN,
    SIGNAL_PARENT,
    SIGNAL_CHILD,
    SIGNAL_HEREDOC
};

/* 
    the main structure of the program: it is being passed as an argument to all
    the fucntions so all the data can be accesed where it needed
 */
typedef struct s_mbox
{
    // TODO: REMOVE THE VARS THAT ARE ONLY FOR ONE CYCLE!!!
    char        **env;
    t_env_var   *env_vars;
    
    char        *inp_orig;
    char        *inp_trim;
    char        *inp_shift;
    char        *inp_expand;
    bool        error_status;
    t_token     *tokens;
    t_token     *tmp_token;
    t_ast      *root;
    t_ast      *tmp_node;
    t_exec      executor;
    int         count_cycles;
}              t_mbox;

/* list of environment variables (definition) */
typedef struct s_env_var
{
    char        *key;
    char        *value;
    struct      s_env_var *next;
}              t_env_var;

/******************************************************************************/

/* input_manager.c */
void	manage_input(t_mbox *mbox);

/* env.c */
void    load_vars_v2(t_mbox *mbox);
char    *get_var_value(t_mbox *mbox, char *key);
void    set_var_value(t_mbox *mbox, char *key, char *value);
void    delete_var(t_mbox *mbox, char *key);
void    free_vars_v2(t_mbox *mbox);

/* env_utils.c */
t_bool   is_var(t_mbox *mbox, char *key);
void	increment_shlvl(t_mbox *mbox);
char    **env_to_matrix(t_mbox *mbox);
void    *free_var_v2(t_env_var *temp);


/* signals.c */
void    update_signals(int sig_state);

/* manage_mbox.c */
void	initialize_box_v2(t_mbox *mbox, char **env);
void    free_cycle_v2(t_mbox *mbox);
void    free_input_strings_v2(t_mbox *mbox);
void    free_tokens_v2(t_mbox *mbox);
void    free_and_close_box_v2(t_mbox *mbox);

/* display_flow.c */
void	print_tokenizer_output(t_mbox *mbox);
void	print_parser_output(t_mbox *mbox);
void	print_executor_output(t_mbox *mbox, int i);

/* general_utils.c */
void    reset_cycle(t_mbox *mbox);
void    exit_failure(t_mbox *mbox);
void    create_error_msg(const char *format, ...);

#endif