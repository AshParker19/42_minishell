/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_shift_seps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/19 02:18:20 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   To prepare the input string for the tokenizer all seperating
 * 			characters need to be found. To mark them frankenshell shifts their
 * 			ASCII value by -126. This makes an easy check for all of them
 * 			possible (ASCII < 0) without loosing their original value.
 * 			
 * 			A seperating char needs to be outside of any quotes to be shifted.
 * 			Those are the characters which we consider as seperating characters:
 * 				- whitespace (SPACE, '\n', '\t', '\v', '\a', '\b', '\f', '\r')
 * 				- pipe	(|)
 * 				- redirections (>, <)
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#shift-separators
 * 
 * @param   mbox        
 * @param   i           
 * @param   quote_state 
 * @return  t_bool      
 */
t_bool	shift_seps(t_mbox *mbox, int i, int quote_state)
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
