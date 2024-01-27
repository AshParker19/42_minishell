/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_shifting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:16:30 by astein            #+#    #+#             */
/*   Updated: 2023/12/19 02:24:35 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief   To prepare the input string for the tokenizer all seperating
 * 			characters need to be found. To mark them frankenshell shifts their
 * 			ASCII value by -126. This makes an easy check for all of them
 * 			possible (ASCII < 0) without loosing their original value.
 * 
 * 			The shifting (aka offseting) is done by the functions:
 * 				- add_offset()
 * 				- remove_offset()
 * 			
 * 			This file contains all the functions related to the shifting of the
 * 			seperating characters.
 * 
 * 			A seperating char needs to be outside of any quotes to be shifted.
 * 			Those are the characters which we consider as seperating characters:
 * 				- whitespace (SPACE, '\n', '\t', '\v', '\a', '\b', '\f', '\r')
 * 				- pipe	(|)
 * 				- redirections (>, <, >>, <<)
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#shift-separators
 * 
 */

# include "frankenshell.h"

/* shifts the receiving char to negative ASCII values (for tokenizer) */
int	add_offset(int c)
{
	return (c - 126);
}

/* shifts the receiving char back to positive ASCII (for tokenizer) */
int	remove_offset(int c)
{
	return (c + 126);
}

/**
 * @brief   Accepts an address of quote_state to update it
 *          
 * IDEA:
 * 		If somwehre at frankenshell we loop through the an input string
 * 		sometimes we need to know if we are inside or outside of contextual
 * 		quotes. This function updates the quote_state variable to the current
 * 		state of the quotes.
 * 
 * LOGIC:
 * 		if quote_state is OUT_Q (the cur_char is outside of contextual quotes)
 * 			if cur_char is a quote
 * 				update quote_state to the cur_char
 * 			else
 * 				quote_state stays OUT_Q
 *		else (the cur_char is inside of contextual quotes)
 * 			if matching quote is found
 * 				update quote_state to OUT_Q
 * 			else
 * 				quote_state stays the same          
 * 
 * @param   quote_state 
 * @param   cur_char    
 * @param   shift       if true the quotes for comparison will be shifted
 */
void	update_quote_state(int *quote_state, char cur_char, t_bool shift)
{
	char	single_q;
	char	double_q;

	single_q = '\'';
	double_q = '"';
	if (shift)
	{
		single_q = add_offset('\'');
		double_q = add_offset('"');
	}
	if (*quote_state == OUT_Q)
	{
		if (cur_char == single_q)
			*quote_state = cur_char;
		else if (cur_char == double_q)
			*quote_state = cur_char;
	}
	else if (*quote_state == single_q)
	{
		if (cur_char == single_q)
			*quote_state = OUT_Q;
	}
	else if (*quote_state == double_q)
		if (cur_char == double_q)
			*quote_state = OUT_Q;
}
