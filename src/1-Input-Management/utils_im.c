/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:05:22 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/01 11:43:10 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   shifts the receiving character to negative ASCII values so it will be used
   for tokenization
*/
int	add_offset(int c)
{
	return (c - 126);
}

/* shifts it back to a needed ASCII value */
int	remove_offset(int c)
{
	return (c + 126);
}
/*
	these functions return true or false depending on the result of checking:
*/

/* if the receiving character is single or double quote */
bool	ft_isqoute(char c)
{
	return (c == '\'' || c == '"');
}

/* if it is one of the separators */
bool	ft_issep(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

/* if it is one of the whitespaces */
bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v');
}
