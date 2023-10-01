/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:02 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/01 11:28:06 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_MANAGER_H
# define INPUT_MANAGER_H

# include "minishell.h"

/******************************************************************************/
/* QUOTE STATES */
# define OUT_Q      0   //OUTSIDE QUOTES

/* VALUE TO SHIFT SPACE CHARACTER */
# define NO_SPACE	-125	//WHITESPACE TO BE IGNORED
/******************************************************************************/

/* data types from other header files */
typedef struct s_minibox t_minibox;

/******************************************************************************/
/* TOKEN HOLDER */
typedef	struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}				t_token;

/* ABSTRACT SYNTAX TREE TO ESTABLISH THE ORDER OF EXECUTION */
typedef struct	s_tree
{
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;
/******************************************************************************/

/* HANDLE QUOTES */
void	mark_seps(t_minibox *minibox, int i, int quote_state);
void 	update_qoute_state(int *quote_state, char cur_char);

/* VARIABLES EXPANSION */
char    find_limiter(char *input, int i);
char    *insert_value(char *input, char *key, char *value, int quote_state);
void	expand_variables(t_minibox *minibox, int k, int k_end, int quote_state);

/* LEXER */
void	tokenize(t_minibox *minibox, int i);
int		add_offset(int c);
int		remove_offset(int c);
bool	ft_isspace(char c);
bool	ft_issep(char c);
bool	ft_isqoute(char c);

/* PARSER */
void	parse(t_minibox *minibox);

#endif

