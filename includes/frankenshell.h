/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frankenshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:05 by astein            #+#    #+#             */
/*   Updated: 2023/12/19 19:32:30 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRANKENSHELL_H
# define FRANKENSHELL_H

/******************************# SYSTEM INCLUDES #*****************************/
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

/*****************************# PROJECT INCLUDES #*****************************/
# include "../libft/libft_printf.h"
# include "config.h"
# include "input_manager.h"
# include "builtins.h"
# include "executor.h"

/**********************************# INFO #************************************/

/* global variable for signal handling */
extern int						g_signal_status;

/* typedefs from the other header files with all the info for mbox */
typedef struct s_env			t_env;
typedef struct s_history		t_history;
typedef struct s_builtin_cmd	t_builtin_cmd;
typedef struct s_exec			t_exec;

/*****************************# DATA STRUCTURES #******************************/

/* 
 *	the main structure of the program: it is being passed as an argument to most
 *	of the functions and contains all the info needed for the program to work.
 *	The file 'manage_mbox.c' contains the functions for initializing and
 *	destroying the mbox instance.
 */
typedef struct s_mbox
{
	char						*inp_orig;
	char						*inp_trim;
	char						*inp_eq;
	char						*inp_shift;
	char						*inp_expand;
	int							consecutive_lt;
	bool						syntax_err_encountered;	//track the first error
	t_env						*env;
	t_list						*history_lst;
	t_token						*tokens;
	t_token						*tmp_token;
	t_ast						*ast;
	t_ast						*tmp_node;
	t_exec						exec;
	int							count_cycles;
	t_bool						info_mode;
}	t_mbox;

/* struct to store all variables as key-value pairs in a linked list */
typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}	t_env;

/* struct to store all the user input in a linked list */
typedef struct s_history
{
	int							index;
	char						*inp;
	t_mbox						*mbox;
}	t_history;

/*********************************# FUNCTIONS #********************************/

/*========================================*/
/*>>>>>>>>>> FOLDER 1_CORE                */
/*========================================*/
/*>>> 0_MBOX.C         */
/*---------------------*/
void	initialize_mbox(t_mbox *mbox, char **env);
void	destroy_mbox(t_mbox *mbox);
t_bool	destroy_mbox_with_exit(t_mbox *mbox, int exit_status);

/*>>> 1_MAIN.C         */
/*---------------------*/
int		main(int ac, char **av, char **env);

/*>>> 2_CYCLE.C        */
/*---------------------*/
void	cycle_main(t_mbox *mbox);
void	reset_cycle(t_mbox *mbox);

/*>>> 3_SHIFTING.C     */
/*---------------------*/
int		add_offset(int c);
int		remove_offset(int c);
void	update_quote_state(int *quote_state, char cur_char, t_bool shift);

/*>>> 4_ENV_VARS.C     */
/*---------------------*/
void	initialize_vars(t_mbox *mbox, char **env);
t_bool	is_var(const t_mbox *mbox, const char *key);
char	*get_var_value(const t_mbox *mbox, const char *key);
char	**get_env_as_matrix(const t_mbox *mbox, const char *put_quotes);
void	set_var_value(t_mbox *mbox, const char *key, const char *value);
void	set_var_value_int(t_mbox *mbox, const char *key, int int_value);
void	increment_shlvl(t_mbox *mbox);
void	unset_var(t_mbox *mbox, const char *key);
void	free_vars(t_mbox *mbox);

/*>>> 5_SIGNALS.C      */
/*---------------------*/
void	conf_sig_handler(int sig_state);

/*>>> 6_ERR_MSG.C	   */
/*---------------------*/
void	err_msg(t_mbox *mbox, int exit_status, const char *format, ...);
void	*syntax_err_msg(t_mbox *mbox, t_token *err_token);













/*========================================*/
/*>>>>>>>>>> FOLDER 2_CYCLE               */
/*========================================*/
/*>>> O_MARK_EQ.C	   */
/*---------------------*/
void	mark_empty_quotes(t_mbox *mbox);

/*>>> 1_shift_seps.c   */
/*---------------------*/
t_bool	shift_seps(t_mbox *mbox, int i, int quote_state);

/*>>> 2_exp_vars.c     */
/*---------------------*/
char	*get_key(char *str, int *i);
t_bool	expand_vars_main(t_mbox *mbox, int k, int quote_state);



// BELO IS OLD AND NOT SORTED FUNCTION!!!
// 0000000-----------------
// ---
// --

void	hd_child(t_mbox *mbox, t_hd hd, int *cur_p);

void	info_put_banner(t_mbox *mbox, char *caption, char *data, char *clr);
void	info_print_input_string(t_mbox *mbox, char *state, char *str, char *clr);
void	info_print_tokenizer(t_mbox *mbox, char *clr);
void	info_print_parser(t_mbox *mbox, char *clr);
void	info_print_executor_banner(t_mbox *mbox, t_bool top_part, char *clr);

/* input_manager.c */



/* signals.c */
void	conf_sig_handler(int sig_state);

/* manage_mbox.c */
void	free_input_strings_v2(t_mbox *mbox);
void	free_tokens_v2(t_mbox *mbox);



/* general_utils.c */
void	err_msg(t_mbox *mbox, int exit_status, const char *format, ...);
void	*syntax_err_msg(t_mbox *mbox, t_token *err_token);

#endif