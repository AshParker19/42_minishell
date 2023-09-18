/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:35:02 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/18 19:11:34 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* TYPES */
# define CMD      1
# define ARG      2
# define PIPE     3
# define REDIR    4
# define HERE_DOC 5
# define DOLLAR_S 6
# define DIGIT    7

typedef struct s_parser
{
	int				type;
	char			*token;
	struct s_parser	*next;
}				t_parser;


// PARSER.C
t_bool	parse_input(char *input);

#endif