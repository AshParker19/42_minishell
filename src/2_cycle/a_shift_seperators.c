/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_shift_seperators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/18 01:12:36 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   accepts an address of quote_state to update it using
 *  		TODO: rewrite because now we have 3 arguments
 *          call by reference and accepts the cur char of the srting
 *          checks the cur quote state and compares it to single or double 
 *          quotes characters.
 *          if quote_state is OUT_Q, means no quote were found before
 *              and is it is now change quote state to aacording
 *              value(single or double quote)
 *          else
 *              means that the quote was found, and is a needed quote occurs
 *              close it and put quote_state to OUT_Q  
 * 
 * @param   quote_state 
 * @param   cur_char 
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




/**
 * @brief   1. marks empty quotes as empty tokens via 'mark_e_q_recursively'
 * 				e.g. "" -> E_
 * 			2. traverses through the string and if quotes_state is Q_OUT,
 *          		if cur char is a context char
 *          			shifts it to negative ASCII value
 * 
 *	CONTEXT CHARS:
 *	 - context quotes						"'
 *	 - separators 							|<>
 *	 - whitespaces (if qoute_state = OUT_Q)	\n\t\v\a\b\f\r (via 'ft_isspace')
 * 
 * @param   mbox 
 * @param   i 
 * @param   quote_state 
 * @return  t_bool 
 */
t_bool	shift_context_chars(t_mbox *mbox, int i, int quote_state)
{
	mbox->inp_shift = ft_strdup(mbox->inp_eq);
	while (mbox->inp_shift[++i])
	{
		if (quote_state == OUT_Q && ft_isqoute(mbox->inp_shift[i]))
		{
			mbox->inp_shift[i] = add_offset(mbox->inp_shift[i]);
			quote_state = mbox->inp_shift[i];
		}
		else if (quote_state == OUT_Q && ft_issep(mbox->inp_shift[i]))
			mbox->inp_shift[i] = add_offset(mbox->inp_shift[i]);
		else if (quote_state == OUT_Q && ft_isspace(mbox->inp_shift[i]))
			mbox->inp_shift[i] = NO_SPACE;
		else if (quote_state == add_offset(mbox->inp_shift[i]))
		{
			mbox->inp_shift[i] = add_offset(mbox->inp_shift[i]);
			quote_state = OUT_Q;
		}
	}
	if (quote_state != OUT_Q)
	{
		err_msg(mbox, 2, "nn", ERR_P, SE_UQ);
		return (ft_false);
	}
	return (ft_true);
}
