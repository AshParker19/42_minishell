/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+ma  +#+           */
/*   Created: 2023/08/07 16:04:05 by astein            #+#    #+#             */
/*   Updated: 2023/11/08 21:56:36 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_signal_status;

/* system includes */
# include <curses.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

//TODO: error checking
//	- don't forget to remove at the end
//	- make protections for other fucntion which can break
//  - when we exit in these cases, we don't care about the exit status, it's always 0
// # define malloc(y) NULL
// # define shift_context_chars(z,c,v) ft_false
// # define fork() -1
// # define pipe(x) -1
// # define dup2(x, y) -1

/* project includes */
# include "../libft/libft_printf.h"
# include "input_manager.h"
# include "builtins.h"
# include "executor.h"
# include "config.h"

/******************************************************************************/

/******************************************************************************/
/* info for mbox */
typedef struct s_env t_env;
typedef struct s_history t_history;
typedef struct s_builtin_cmd t_builtin_cmd;
typedef struct s_exec t_exec;

/* 
    the main structure of the program: it is being passed as an argument to all
    the fucntions so all the data can be accesed where it needed
 */
typedef struct s_mbox
{
    t_env   *env;
    
    char        *inp_orig;
    char        *inp_trim;
    char        *inp_shift;
    char        *inp_expand;
	int			consecutive_lt;
    bool        error_status;
	t_list		*history_lst;
    t_token     *tokens;
    t_token     *tmp_token;
    t_ast      *root;
    t_ast      *tmp_node;
    t_exec      executor;
    int         count_cycles;
	t_bool		stop_heredoc;
    t_bool      print_info;
}              t_mbox;

/* list of environment variables (definition) */
typedef struct s_env
{
    char        *key;
    char        *value;
    struct      s_env *next;
}              t_env;

/* list element which stores all the input in a t_list*/
typedef struct  s_history
{
    int                 index;
    char                *inp;
	t_mbox				*mbox;
}               t_history;

/******************************************************************************/

/* input_manager.c */
void	input_main(t_mbox *mbox);

/* env.c */
void	load_vars_v2(t_mbox *mbox, char **env);
char    *get_var_value(const t_mbox *mbox,const char *key);
void    delete_var(t_mbox *mbox, const char *key);
void    free_vars_v2(t_mbox *mbox);

/* env_utils.c */
t_bool   is_var(const t_mbox *mbox, const char *key);
void	increment_shlvl(t_mbox *mbox);
char    **env_to_matrix(const t_mbox *mbox, const char *put_quotes);
void    *free_var_v2(t_env *temp);


/* env_utils2.c */
void    set_var_value(t_mbox *mbox, const char *key, const char *value);
void    set_var_value_int(t_mbox *mbox, const char *key, int int_value);


/* signals.c */
void    update_signals(int sig_state);

/* manage_mbox.c */
void	initialize_box_v2(t_mbox *mbox);
void    free_cycle_v2(t_mbox *mbox);
void    free_input_strings_v2(t_mbox *mbox);
void    free_tokens_v2(t_mbox *mbox);
void    free_and_close_box_v2(t_mbox *mbox);

/* display_flow.c */
void	put_headline(char *caption, char *data, char *clr);
void	display_info_str(t_mbox *mbox, char *state, char *str);
void	print_tokenizer_output(t_mbox *mbox);

/* display_flow2.c */
void	print_line(char symbol, char *clr, t_bool app_new_line);
void	print_parser_output(t_mbox *mbox, t_bool top_part);
void	print_executor_output(t_mbox *mbox, t_bool top_part);

/* general_utils.c */
void    reset_cycle(t_mbox *mbox);
t_bool    err_free_and_close_box(t_mbox *mbox, int exit_status);
void    err_msg(t_mbox *mbox, int exit_status, const char *format, ...);
void    put_info_msg(t_mbox *mbox, const char *format, ...);
void	*create_syntax_err(t_mbox *mbox, t_token *err_token);

#endif