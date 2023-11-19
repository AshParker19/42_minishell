/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:07:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/19 18:17:36 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/******************************# ERROR MESSAGES #******************************/

# define CS                 ": "
# define SQ                 "'"
# define CMD_N_FND          "command not found"
# define NO_FOD             "No such file or directory"
# define IS_DIR             "Is a directory"
# define NO_DIR             "Not a directory"
# define NO_PERM            "Permission denied"
# define NO_VI              "not a valid identifier"
# define SE_LT              "syntax error near unexpected token `<'"
# define SE_GT              "syntax error near unexpected token `>'"
# define SE_UT              "syntax error near unexpected token `"
# define SE_NL              "syntax error near unexpected token `newline'"
# define SE_UQ 				"syntax error: unclosed quotes"
# define CD                 "cd: "
# define CD_H               "cd: HOME not set"
# define CD_A               "cd: too many arguments"
# define WA_F 				"wrong argument!\nuse: -i ('--info')"
# define WN   				"wrong number of arguments!"
# define W_HD 				"warning: here-document at line "
# define DW 				" delimited by end-of-file (wanted `"
# define NAR				"numeric argument required"
# define TMA				"too many arguments"

/**********************************# COLORS #**********************************/

# define GREEN 				"\033[0;32m"
# define RED 				"\033[0;31m"
# define LIGHT_RED  		"\033[38;5;203m"
# define YELLOW 			"\x1b[33m"
# define CYAN 				"\x1b[36m"
# define PURPLE 			"\x1b[35m"
# define RESET 				"\033[0m"

/*********************************# SIGNALS #**********************************/

# define SIGNAL_NEW_LINE 1
# define SIGNAL_EXIT_HD 2
# define NO_EXIT_STATUS -99999

enum e_signal_state
{
	SIGNAL_MAIN,
	SIGNAL_PARENT,
	SIGNAL_CHILD,
	SIGNAL_HEREDOC
};

/******************************# PROMPT FORMAT #*******************************/
/* promt strings */
// # define PROMPT      "\x1b[36mfrankenshell-->\033[0m "
// # define ERR_P  "\033[38;5;203mfrankenshell:\033[0m "
// # define HEREDOC_PROMPT "frankendoc> "
/* test prompts */
# define PROMPT								"minishell:"
# define ERR_P          					"minishell: "
# define HEREDOC_PROMPT 					"> "

/******************************# INFINITE LOOPS #******************************/

# define FRANKENSHELL_RISES_AMIDTS_DEATH	1
# define FRANCENDOC_ECHOES_IN_ETERNITY		1

/****************************# EXIT STATUS STRING #****************************/

# define EXIT_SUCCESS_STR 					"0"
# define EXIT_FAILURE_STR 					"1"

/********************************# TOKENIZER #*********************************/

/* token types for the t_token list */
enum e_token_type
{
	WORD_TOKEN,
	PIPE_TOKEN,
	RED_IN_TOKEN,
	RED_OUT_TOKEN,
};

/* token types for t_ast */
enum e_node_type
{
	CMD_NODE,
	ARG_NODE,
	PIPE_NODE,
	RED_IN,
	RED_IN_HD,
	RED_OUT_TR,
	RED_OUT_AP
};

/* right or left branch of the ast */
enum e_three_branch
{
	RIGHT,
	LEFT
};

/*********************************# EXECUTOR #*********************************/

/* command state  */
enum e_cmd_type
{
	SINGLE_CMD,
	FIRST_CMD,
	MIDDLE_CMD,
	LAST_CMD
};

/* file descriptors for commands */
enum e_cmd_dir
{
	CMD_IN,
	CMD_OUT
};

/* file descriptors for pipe */
enum e_pipe_side
{
	P_RIGHT,
	P_LEFT
};

#endif
