/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frankenshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:05 by astein            #+#    #+#             */
/*   Updated: 2023/12/15 19:39:30 by astein           ###   ########.fr       */
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
# include "executor.h"
# include "builtins.h"

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
	the main structure of the program: it is being passed as an argument to most
	of the functions and contains all the info needed for the program to work.
	The file 'manage_mbox.c' contains the functions for initializing and
	destroying the mbox instance.
 */
typedef struct s_mbox
{
	char						*inp_orig;
	char						*inp_trim;
	char						*inp_shift;
	char						*inp_expand;
	int							consecutive_lt;
	bool						error_status;
	t_env						*env;
	t_list						*history_lst;
	t_token						*tokens;
	t_token						*tmp_token;
	t_ast						*root;
	t_ast						*tmp_node;
	t_exec						executor;
	int							count_cycles;
	t_bool						print_info;
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
/*>>>>>>>>>> 0 CORE                       */
/*========================================*/
/*>>> MAIN.C           */
/*---------------------*/
int		main(int ac, char **av, char **env);

/*>>> MANAGE_MBOX.C    */
/*---------------------*/
void	initialize_mbox(t_mbox *mbox, char **env);
void	destroy_mbox(t_mbox *mbox);
t_bool	destroy_mbox_with_exit(t_mbox *mbox, int exit_status);

/*
/*========================================*/
/*>>>>>>>>>> 1 INPUT MANAGER */
/*========================================*/

/*========================================*/
/*>>>>>>>>>> 2 EXECUTOR */
/*========================================*/

/*========================================*/
/*>>>>>>>>>> 3 BUILTINS */
/*========================================*/

/*========================================*/
/*>>>>>>>>>> 4 DEBUG */
/*========================================*/



/* input_manager.c */
void	input_main(t_mbox *mbox);

/* env.c */
void	load_vars_v2(t_mbox *mbox, char **env);
char	*get_var_value(const t_mbox *mbox, const char *key);
void	delete_var(t_mbox *mbox, const char *key);
void	free_vars_v2(t_mbox *mbox);

/* env_utils.c */
t_bool	is_var(const t_mbox *mbox, const char *key);
void	increment_shlvl(t_mbox *mbox);
char	**env_to_matrix(const t_mbox *mbox, const char *put_quotes);
void	*free_var_v2(t_env *temp);

/* env_utils2.c */
void	set_var_value(t_mbox *mbox, const char *key, const char *value);
void	set_var_value_int(t_mbox *mbox, const char *key, int int_value);

/* signals.c */
void	conf_sig_handler(int sig_state);

/* manage_mbox.c */
void	free_input_strings_v2(t_mbox *mbox);
void	free_tokens_v2(t_mbox *mbox);

/* display_flow.c */
void	put_headline(char *caption, char *data, char *clr);
void	display_info_str(t_mbox *mbox, char *state, char *str);
void	print_tokenizer_output(t_mbox *mbox);

/* display_flow2.c */
void	print_line(char symbol, char *clr, t_bool app_new_line);
void	print_parser_output(t_mbox *mbox, t_bool top_part);
void	print_executor_output(t_mbox *mbox, t_bool top_part);

/* general_utils.c */
void	reset_cycle(t_mbox *mbox);
void	err_msg(t_mbox *mbox, int exit_status, const char *format, ...);
void	*create_syntax_err(t_mbox *mbox, t_token *err_token);

#endif