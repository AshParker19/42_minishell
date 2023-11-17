/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:02 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/17 17:24:36 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_MANAGER_H
# define INPUT_MANAGER_H

/******************************************************************************/
/* QUOTE STATES */
# define OUT_Q      0   //OUTSIDE QUOTES

/* VALUE TO SHIFT SPACE CHARACTER */
# define EMPTY_TOKEN	-126	//MARK THE NEED OF AN EMPTY TOKEN
# define NO_SPACE	    -125	//WHITESPACE TO BE IGNORED
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

/******************************************************************************/

/* HANDLE QUOTES */
t_bool  shift_context_chars(t_mbox *mbox, int i, int quote_state);
void 	update_quote_state(int *quote_state, char cur_char, t_bool shift);

/* VARIABLES EXPANSION */
t_bool  expand_variables(t_mbox *mbox, int k, int quote_state);

/* HEREDOC UTILS*/
char    *extract_limiter(t_mbox *mbox, int *k, int *quote_state, char *lim);


/* TOKENIZER */
t_bool	tokenize(t_mbox *mbox, int i);
int		add_offset(int c);
int		remove_offset(int c);
t_bool	ft_isspace(char c);
t_bool	ft_issep(char c);
t_bool	ft_isqoute(char c);
t_bool  check_sp(char *no_space);
t_bool	check_space_between_redir(t_mbox *mbox, char *str1, char *str2);
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