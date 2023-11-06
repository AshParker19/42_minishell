/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:02 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/06 15:32:28 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_MANAGER_H
# define INPUT_MANAGER_H

/******************************************************************************/
/* QUOTE STATES */
# define OUT_Q      0   //OUTSIDE QUOTES

/* VALUE TO SHIFT SPACE CHARACTER */
# define NO_SPACE	-125	//WHITESPACE TO BE IGNORED
// # define FLG_IGNORE	-126	//WHITESPACE TO BE IGNORED
/******************************************************************************/

/* data types from other header files */
typedef struct s_mbox t_mbox;

/******************************************************************************/
/* TOKEN HOLDER */
typedef	struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}				t_token;

/* ABSTRACT SYNTAX TREE TO ESTABLISH THE ORDER OF EXECUTION */
typedef struct	s_ast
{
	int				type;
	char   			*content;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

/* TOKEN TYPES FOR THE T_TOKEN LIST */
enum e_token_type
{
    WORD_TOKEN,
    PIPE_TOKEN,
    RED_IN_TOKEN,
    RED_OUT_TOKEN,
};

/* TOKEN TYPES FOR T_AST */
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

/* RIGHT OR LEFT BRANCH OF THE AST */
enum e_three_branch
{
    RIGHT,
    LEFT
};
/******************************************************************************/

/* HANDLE QUOTES */
t_bool  mark_seps(t_mbox *mbox, int i, int quote_state);
void 	update_qoute_state(int *quote_state, char cur_char);

/* VARIABLES EXPANSION */
t_bool  expand_variables(t_mbox *mbox, int k, int k_end, int quote_state);

/* HEREDOC UTILS*/
char    *extract_limiter(t_mbox *mbox, int *k, int *quote_state);


/* TOKENIZER */
t_bool	tokenize(t_mbox *mbox, int i);
int		add_offset(int c);
int		remove_offset(int c);
t_bool	ft_isspace(char c);
t_bool	ft_issep(char c);
t_bool	ft_isqoute(char c);
t_bool  check_sp(char *no_space);
t_bool	check_space_between_redir(char *str1, char *str2);
int     get_token_type(char c);
void    free_tokens_v2(t_mbox *mbox);

/* PARSER */
t_bool	parse(t_mbox *mbox);
t_ast  *ast_create_node(int node_type);
void    free_ast_v2(t_ast *root);
void    connect_subtree(t_ast **root, t_ast *node_to_add, int on_right);
t_bool    validate_token(t_token *token, int next_amount, int token_type);

/* functions for BNF notation to build an AST */
/* job */
t_ast *job_main(t_mbox *mbox);

/* command */
t_ast *command_main(t_mbox *mbox);

/* token_list */
void    token_list_main(t_mbox *mbox);

/* redir */
t_ast *redir_main(t_mbox *mbox);
t_ast *redir_in_main(t_mbox *mbox);
t_ast *redir_out_main(t_mbox *mbox);
/**********************************************/

#endif