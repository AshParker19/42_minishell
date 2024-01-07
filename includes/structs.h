/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:02 by anshovah          #+#    #+#             */
/*   Updated: 2024/01/07 11:55:55 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/**************************# ALL FRANKENSHELL STRUCTS #************************/
typedef struct s_builtin_cmd	t_builtin_cmd;
typedef struct s_exec			t_exec;
typedef struct s_io				t_io;
typedef struct s_env			t_env;
typedef struct s_history		t_history;
typedef struct s_token			t_token;
typedef struct s_ast			t_ast;
typedef struct s_hd				t_hd;
typedef struct s_mbox			t_mbox;
typedef struct s_builtin_cmd	t_builtin_cmd;
typedef struct s_exec			t_exec;
typedef struct s_io				t_io;

/**************************# STRUCT DEFINITIONS #******************************/

/* bultins function pointer typedef */
typedef void	(*t_builtin_function)(t_mbox *mbox, t_ast *arg_node);

/* struct for each builtin */
typedef struct s_builtin_cmd
{
	char				*cmd_name;
	t_builtin_function	func_name;
}	t_builtin_cmd;

/* data for input/output manipulations */
typedef struct s_io
{
	t_bool				use_pipe[2];
	int					cmd_fd[2];
	int					dup_fd[2];
	int					prev_pipe[2];
}	t_io;

/*  data for execution */
typedef struct s_exec
{
	t_builtin_cmd		builtins[12];
	t_io				io;
	int					*pid;
	int					pid_index;
}	t_exec;

/**
 *	The main structure of the program: it is being passed as an argument to most
 *	of the functions and contains all the info needed for the program to work.
 *	The file '0_mbox.c' contains the functions for initializing andndestroying
  * the mbox instance.
 */
typedef struct s_mbox
{
	char				*inp_orig;				// (  echo $USER "" > file)
	char				*inp_trim;				// (echo $USER "" > file)
	char				*inp_eq;				// (echo $USER E_ > file)
	char				*inp_shift;				// (echo $USER E_ O file)
	char				*inp_expand;			// (echo astein E_ O file)
	int					consecutive_lt;			// << lol << lol
	bool				syntax_err_encountered;	// track the first error
	t_env				*env;					// env vars as linked list
	t_list				*history_lst;			// history as linked list
	t_token				*tokens;				// tokens as linked list
	t_token				*tmp_token;				// temp token for building ast
	t_ast				*ast;					// root of the ast
	t_ast				*tmp_node;				// temp node for building ast
	t_exec				exec;					// execution data
	int					count_cycles;			// cycles for heredoc error msg
	t_bool				info_mode;				// info mode on/off
}	t_mbox;

/* struct to store all variables as key-value pairs in a linked list */
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

/* struct to store all the user input in a linked list */
typedef struct s_history
{
	int					index;
	char				*inp;
	t_mbox				*mbox;
}	t_history;

/* token holder */
typedef struct s_token
{
	int					type;
	char				*value;
	struct s_token		*next;
}	t_token;

/* abstract syntax tree to establish the order of execution */
typedef struct s_ast
{
	int					type;
	int					cmd_pos;
	char				*content;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

/* heredoc */
typedef struct s_hd
{
	int					*fd;
	char				*lim;
	char				*cur_line;
}	t_hd;

#endif
