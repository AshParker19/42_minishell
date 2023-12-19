/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_shift_seperators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/18 22:30:27 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"






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
