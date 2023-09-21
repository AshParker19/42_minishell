/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:02 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/21 15:11:05 by anshovah         ###   ########.fr       */
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

typedef	struct s_token
{
	int				type;
	char			*token_value;
	struct s_token	*next;
}				t_token;

// typedef struct s_parser
// {
// 	int				type;
// 	char			*token;
// 	struct s_parser	*next;
// }				t_parser;

/* parsing utils */
t_token	*ft_addback(t_token *head, char *token_v, int type);
int		ft_isspace(char c);
char	*skip_spaces(char *str);
bool	special_characters(char c, int i);

// PARSER.C
t_bool	parse_input(char *input);

#endif