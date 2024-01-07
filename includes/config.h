/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:07:39 by anshovah          #+#    #+#             */
/*   Updated: 2024/01/07 11:49:53 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/**********************************# COLORS #**********************************/
# define GREEN 			"\033[0;32m"
# define RED 			"\033[0;31m"
# define LIGHT_RED  	"\033[38;5;203m"
# define YELLOW 		"\x1b[33m"
# define CYAN 			"\x1b[36m"
# define PURPLE 		"\x1b[35m"
# define B_WHITE		"\x1b[97m"
# define RESET 			"\033[0m"

/**********************************# PROMPT FORMAT #***************************/
/**
 *	The escape sequence '\001' is used to tell readline that trailing chars
 *	are non printing chars (which in this case is the color sequence)
 *		
 *	The escape sequence '\002' is used to tell readline that trailing chars
 *	are printing chars
*/
# define PROMPT 		"\001\x1b[36m\002frankenshell--> \001\033[0m\002"
# define ERR_P  		"\001\033[38;5;203m\002frankenshell: \001\033[0m\002"
# define HEREDOC_PROMPT	"\001\x1b[33m\002frankendoc> \001\033[0m\002"

/**********************************# INFO MODE #*******************************/
# define BANNER_WIDTH 	80

/**********************************# SIGNALS #*********************************/
# define SIGNAL_NEW_LINE 1
# define SIGNAL_EXIT_HD 2
# define NO_EXIT_STATUS -99999

enum e_signal_state
{
	SIG_STATE_MAIN,
	SIG_STATE_PARENT,
	SIG_STATE_CHILD,
	SIG_STATE_CHILD_BUILTIN,
	SIG_STATE_HD_CHILD,
	SIG_STATE_IGNORE
};

/**********************************# PARSING #*********************************/
# define OUT_Q     		 0		// outside quote state
# define NO_SPACE	    -125 	// indicate a ws character to be ignored
# define EMPTY_TOKEN	-126	// indicate the necessity of an empty token

/**********************************# TOKENIZER #*******************************/
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

/**********************************# EXECUTOR #********************************/
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

/**********************************# ERROR MESSAGES #**************************/
# define CS             ": "
# define SQ          	"'"
# define CMD_N_FND      "command not found"
# define NO_FOD         "No such file or directory"
# define IS_DIR         "Is a directory"
# define NO_DIR         "Not a directory"
# define NO_PERM        "Permission denied"
# define NO_VI          "not a valid identifier"
# define SE_LT          "syntax error near unexpected token `<'"
# define SE_GT          "syntax error near unexpected token `>'"
# define SE_UT          "syntax error near unexpected token `"
# define SE_NL          "syntax error near unexpected token `newline'"
# define SE_UQ 			"syntax error: unclosed quotes"
# define CD             "cd: "
# define CD_H           "cd: HOME not set"
# define CD_A           "cd: too many arguments"
# define WA_F 			"wrong argument!\nuse: -i ('--info')"
# define WN   			"wrong number of arguments!"
# define W_HD 			"warning: frankendoc at line "
# define DW 			" delimited by end-of-file (wanted `"
# define NAR			"numeric argument required"
# define TMA			"too many arguments"

#endif
