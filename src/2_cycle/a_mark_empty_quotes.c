/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_mark_empty_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:37:31 by astein            #+#    #+#             */
/*   Updated: 2023/12/18 01:16:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief   This file copies the `inp_trim` string to `inp_eq` and
 *			marks the empty quotes as EMPTY_TOKEN or NO_SPACE.
 *
 *			EXAMPLES: (_ = NO_SPACE, E = EMPTY_TOKEN)
 * 				no	| inp_trim		| inp_eq
 * 				----| --------------|------------------
 * 				1.	| ""			| E_
 * 				2.	| ''			| E_
 * 				3.	| hi""			| hi
 * 				4.	| hi''			| hi
 * 				5.	| ""hi			| hi
 * 				6.	| ''hi			| hi
 * 				7.	| '""'			| ""
 * 				8.	| "''"			| ''
 * 				9.	| """"			| E___
 * 				10.	| "" "" "'hi"	| E_ E_ "'hi"
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#mark-empty-quotes
 */

#include "frankenshell.h"

static void	mark_e_q_recursively(t_mbox *mbox, int i, t_bool check_prev, int qs);

static t_bool	is_make_empty(t_mbox *mbox, int i, int qs, t_bool check_prev)
{
	t_bool	make_empty;

	make_empty = ft_true;
	if (!ft_isqoute(mbox->inp_trim[i]))
		return (ft_false);
	if (check_prev && i > 0 && !ft_isspace(mbox->inp_trim[i - 1]))
		return (ft_false);
	if (mbox->inp_trim[i + 1] != qs)
		return (ft_false);
	if (mbox->inp_trim[i + 1] && mbox->inp_trim[i + 2]
		&& !ft_isspace(mbox->inp_trim[i + 2]))
	{
		if (ft_isqoute(mbox->inp_trim[i + 2]))
			mark_e_q_recursively(mbox, i + 2, ft_false, OUT_Q);
		else
			make_empty = ft_false;
	}
	return (make_empty);
}

/**
 * @brief 
 * 

 * THIS function uses a flag to check if its called recurseuvleyyy		
 * RULE - SPECIAL CASE EMPTY QUOTES -> EMPTY TOKENS
 * THIS SPECAIL CASE CAN ONLY HAPPEN IF BEFORE AND AFTER THERE ARE WS 
 * (or beginning / end of string)
 * 
 * all cases can only occure if we are in OUT QOUTE STATE and
 * and the qoute state changes (found a qoute) 	(index i)
 * and the previous char is a whitespace
 *                          		(index i-1) 	(if i=0 ignore this check)
 * and the next char is a matching qoute 	
 *                              (index i+1) 	(if i+1 = \0 ignore this check)
 * and the next next char is a whitespace
 *                                  (index i+2)	(if i+2 = \0 ignore this check)
 * if this fails call recursively
 * 
 * if the function above fails it only means that we dont create empty tokens.
 * the input could still be valid or invalid this function doesnt care about it,
 * since it is the job of 'shift_context_chars' and 'tokenize'
 * 
 * @param mbox 
 * @param i 
 * @param check_prev 
 * 	This parameter is used to mark if the previous char needs to be checked
 * 	also we use it to mark if the function is called recursively so we can
 * 	terminate the recursion before the end of the string
 * @param qs 
 */
static void	mark_e_q_recursively(t_mbox *mbox, int i, t_bool check_prev, int qs)
{
	while (mbox->inp_trim[i])
	{
		update_quote_state(&qs, mbox->inp_trim[i], ft_false);
		if (qs != OUT_Q)
		{
			if (is_make_empty(mbox, i, qs, check_prev))
			{
				if (check_prev)
					mbox->inp_eq[i] = EMPTY_TOKEN;
				else
					mbox->inp_eq[i] = NO_SPACE;
				mbox->inp_eq[i + 1] = NO_SPACE;
				i++;
				update_quote_state(&qs, mbox->inp_trim[i], ft_false);
			}
		}
		if (!check_prev)
			return ;
		i++;
	}
}

void	mark_empty_quotes(t_mbox *mbox)
{
	mbox->inp_eq = ft_strdup(mbox->inp_trim);
	mark_e_q_recursively(mbox, 0, ft_true, OUT_Q);	
}
