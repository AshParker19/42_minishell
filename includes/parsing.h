/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:02 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/24 20:54:02 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* TYPES */
// # define CMD      1
// # define ARG      2
// # define PIPE     3
// # define REDIR    4
// # define HERE_DOC 5
// # define DOLLAR_S 6
// # define DIGIT    7

# define WORD		1
# define PIPE		2
# define DOLLAR		3
# define DB_QUOTE	4
# define SN_QUOTE	5
# define REDIREC	6

/* data types from other header files */
typedef struct s_minibox t_minibox;

typedef	struct s_token
{
	int				type;
	char			*token_value;
	struct s_token	*next;
}				t_token;

/* parsing utils */
t_token	*ft_addback(t_token *head, char *token_val, int type);
int		ft_isspace(char c);
char	*skip_spaces(char *str);
bool	special_characters(char c, int i);

/* expand_vars.c */
char	*find_key(char *input, int i);
char	*expand_variables(t_minibox *minibox, int i, int j);

// PARSER.C
t_bool	parse_input(t_minibox *minibox);

#endif