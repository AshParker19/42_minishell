/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shifter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/04 12:04:58 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	empty_quotes(t_mbox *mbox, int i, t_bool check_prev, int qs);

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
 * @brief	
 * 
 * @param mbox 
 * @param i 
 * @param qs 
 * @param check_prev 
 * @return t_bool 
 */
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
			empty_quotes(mbox, i + 2, ft_false, OUT_Q);
		else
			make_empty = ft_false;
	}
	return (make_empty);
}

/**
 * @brief 
 * 
 * no	input		output
 * ----------------------------------------
 * 1.	""			E_							legend:
 * 2.	''			E_								@ = shiftet value
 * 3.	hi""		hi								_ = NO_SPACE
 * 4.	hi''		hi								E = EMPTY_TOKEN
 * 5.	""hi		hi
 * 6.	''hi		hi
 * 7.	'""'		""
 * 8.	"''"		''
 * 9.	""""		E___
 * 10.	"" "" "'hi"	E_ E_ "'hi"
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
static void	empty_quotes(t_mbox *mbox, int i, t_bool check_prev, int qs)
{
	while (mbox->inp_trim[i])
	{
		update_quote_state(&qs, mbox->inp_trim[i], ft_false);
		if (qs != OUT_Q)
		{
			if (is_make_empty(mbox, i, qs, check_prev))
			{
				if (check_prev)
					mbox->inp_shift[i] = EMPTY_TOKEN;
				else
					mbox->inp_shift[i] = NO_SPACE;
				mbox->inp_shift[i + 1] = NO_SPACE;
				i++;
				// mbox->inp_trim[i] = mbox->inp_trim[i];
				update_quote_state(&qs, mbox->inp_trim[i], ft_false);
			}
		}
		if (!check_prev)
			return ;
		i++;
	}
}

/**
 * @brief   1. marks empty quotes as empty tokens via 'empty_quotes'
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
	mbox->inp_shift = ft_strdup(mbox->inp_trim);
	empty_quotes(mbox, 0, ft_true, OUT_Q);
	display_info_str(mbox, "input empty qs", mbox->inp_shift);
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
