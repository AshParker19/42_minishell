/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:02 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/25 18:49:31 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* TYPES */
# define WORD		1
# define PIPE		2
# define DOLLAR		3
# define DB_QUOTE	4
# define SN_QUOTE	5
# define REDIREC	6

/* data types from other header files */
typedef struct s_minibox t_minibox;

/* TOKEN HOLDER*/
typedef	struct s_token
{
	int				type;
	char			*token_value;
	struct s_token	*next;
}				t_token;

/* ABSTRACT SYNTAX TREE TO ESTABLISH THE ORDER OF EXECUTION */
typedef struct	s_tree
{
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

/* VARIABLES EXPANSION*/
char	*find_key(char *input, int i);
void	expand_variables(t_minibox *minibox, int i, int j);

/* LEXER */
t_token	*ft_addback(t_token *head, char *token_val, int type);
int		ft_isspace(char c);
char	*skip_spaces(char *str);
bool	special_characters(char c, int i);
void	tokenize(t_minibox *minibox);

/* PARSER */
void	parse(t_minibox *minibox);

#endif