/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:07:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/17 17:36:04 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/******************************# ERROR MESSAGES #******************************/

// THOSE I ALREADY USE!!!!
# define MSG_CS ": "	//COLON SPACE
# define MSG_CMD_N_FND "command not found"
# define MSG_NO_FOD "No such file or directory"
# define MSG_NO_PERM "Permission denied"
# define MSG_IS_DIR "Is a directory"
// ===================================
# define MSG_SE_LT "syntax error near unexpected token `<'"
# define MSG_CD "cd: "

/**********************************# COLORS #**********************************/

# define GREEN 		"\033[0;32m"
# define RED 		"\033[0;31m"
# define LIGHT_RED  "\033[38;5;203m"
# define YELLOW 	"\x1b[33m"
# define CYAN 		"\x1b[36m"
# define PURPLE 	"\x1b[35m"
# define RESET 		"\033[0m"

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
// # define ERR_PROMPT  "\033[38;5;203mfrankenshell:\033[0m "
// # define HEREDOC_PROMPT "frankendoc> "
/* test prompts */
# define PROMPT			"minishell:"
# define ERR_PROMPT 	"minishell: "
# define HEREDOC_PROMPT "> "

/******************************# INFINITE LOOPS #******************************/

# define FRANKENSHELL_RISES_AMIDTS_DEATH	1
# define FRANCENDOC_ECHOES_IN_ETERNITY		1

/****************************# EXIT STATUS STRING #****************************/

# define EXIT_SUCCESS_STR "0"
# define EXIT_FAILURE_STR "1"

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
    CMD_IN,       //    stdin 0    std out 1
    CMD_OUT
};

/* file descriptors for pipe */
enum e_pipe_side
{
    P_RIGHT,  //     1 in   ->     0 out
    P_LEFT
};

#endif
