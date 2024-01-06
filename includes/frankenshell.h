/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frankenshell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:05 by astein            #+#    #+#             */
/*   Updated: 2024/01/06 19:40:26 by astein           ###   ########.fr       */
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
# include "structs.h"
# include "builtins.h"
# include "executor.h"

/**********************************# INFO #************************************/
extern int						g_signal_status;	//global variable for signal handling

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

/*>>> 7_UTILS.C	       */
/*---------------------*/
t_bool	ft_isqoute(char c);
t_bool	ft_issep(char c);
t_bool	ft_isspace(char c);


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

/*>>> 3_tokenize.c     */
/*---------------------*/
t_bool	tokenize(t_mbox *mbox, int i);
void	free_tokens(t_mbox *mbox);

/*>>> 4_parse.c        */
/*---------------------*/
t_ast	*ast_create_node(int node_type);
t_bool	validate_token(t_token *token, int next_amount, int token_type);
void	free_ast(t_ast *ast);
void	connect_subtree(t_ast **ast, t_ast *node_to_add, int on_right);
t_bool	parse(t_mbox *mbox);

/*========================================*/
/*>>>>>>>>>> FOLDER 3_PARSER              */
/*========================================*/
/*>>> 1_job.c          */
/*---------------------*/
t_ast	*job_main(t_mbox *mbox);

/*>>> 2_command.c      */
/*---------------------*/
t_ast	*command_main(t_mbox *mbox);

/*>>> 3_token_list.c   */
/*---------------------*/
void	token_list_main(t_mbox *mbox);

/*>>> 4_redir.c        */
/*---------------------*/
t_ast	*redir_main(t_mbox *mbox);

/*>>> 5_redir_in.c     */
/*---------------------*/
t_ast	*redir_in_main(t_mbox *mbox);

/*>>> 5_redir_out.c    */
/*---------------------*/
t_ast	*redir_out_main(t_mbox *mbox);

/*========================================*/
/*>>>>>>>>>> FOLDER 4_BUILTINS            */
/*========================================*/
/*>>> 42.c             */
/*---------------------*/
void	builtin_header(t_mbox *mbox, t_ast *arg_node);

/*>>> cd.c             */
/*---------------------*/
void	builtin_cd(t_mbox *mbox, t_ast *arg_node);

/*>>> echo.c           */
/*---------------------*/
void	builtin_echo(t_mbox *mbox, t_ast *arg_node);

/*>>> env.c            */
/*---------------------*/
void	builtin_env(t_mbox *mbox, t_ast *arg_node);

/*>>> exit.c           */
/*---------------------*/
void	builtin_exit(t_mbox *mbox, t_ast *arg_node);

/*>>> export.c         */
/*---------------------*/
void	builtin_export(t_mbox *mbox, t_ast *arg_node);

/*>>> export_utils.c   */
/*---------------------*/
void	case_equal_sign(t_mbox *mbox, t_ast *arg_node, t_bool *fnd_err, char *equal_sign);
void	case_no_equal_sign(t_mbox *mbox, t_ast *arg_node, t_bool *fnd_err);

/*>>> help.c           */
/*---------------------*/
void	builtin_help(t_mbox *mbox, t_ast *arg_node);

/*>>> history.c        */
/*---------------------*/
void	builtin_history(t_mbox *mbox, t_ast *arg_node);

/*>>> infomode.c       */
/*---------------------*/
void	builtin_infomode(t_mbox *mbox, t_ast *arg_node);

/*>>> pwd.c            */
/*---------------------*/
void	builtin_pwd(t_mbox *mbox, t_ast *arg_node);

/*>>> unset.c          */
/*---------------------*/
void	builtin_unset(t_mbox *mbox, t_ast *arg_node);









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



/* general_utils.c */
void	err_msg(t_mbox *mbox, int exit_status, const char *format, ...);
void	*syntax_err_msg(t_mbox *mbox, t_token *err_token);

#endif