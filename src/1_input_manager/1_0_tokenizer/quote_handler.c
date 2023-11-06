/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/06 18:20:52 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief   accepts an address of quote_state to update it using
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
void update_qoute_state(int *quote_state, char cur_char, t_bool shift)
{
    char    single_q;
    char    double_q;

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

static void   quote_after_quote(t_mbox *mbox, int *i, int *quote_state)
{
    char    prev_quote;
    int     j;

    prev_quote = mbox->inp_shift[*i];
        // if (mbox->inp_shift[i + 1] != prev_quote)
            // {
            //     create_err_msg("nnnnn", ERR_PROMT, "syntax error: unexpected unpaired ", ft_chr2str('"'),
            //         ft_chr2str(mbox->inp_shift[i + 1]), ft_chr2str('"'));
            //     return (ft_false);
            // }
    j = *i;
    while (ft_isqoute(mbox->inp_shift[j])) //FIXME: echo "''" --> ''  echo '""'--> ""   echo """" --> empty token
        j++;
    if (mbox->inp_shift[*i - 1] > 0)
    {
        j = *i;
        while (ft_isqoute(mbox->inp_shift[j]))
        {
            mbox->inp_shift[j] = add_offset(mbox->inp_shift[j]);
            j++; 
        }
    }
    else if (mbox->inp_shift[j]  != '\0'
        && !ft_isqoute(mbox->inp_shift[j + 1]) && !ft_isspace(mbox->inp_shift[j]))
    {
        j = *i + 1;
        while (ft_isqoute(mbox->inp_shift[j]))
        {
            mbox->inp_shift[j] = add_offset(mbox->inp_shift[j]);
            j--;  
        }
    }
    *i += 2;  //should be dynamic
    *quote_state = OUT_Q;
}

// static void 

/**
 * @brief 
 * 
 * legend:
	@ = shiftet value
	_ = NO_SPACE
	° = EMPTY_TOKEN
no	input		output
----------------------------------------
1.	""		°_
2.	''		°_
3.	hi""		hi
4.	hi''		hi
5.	""hi		hi
6.	''hi		hi
7.	'""'		""
8.	"''"		''
9.	""""		°___
10.	"" "" "'hi"	°_ °_ "'hi"

THIS function uses a flag to check if its called recurseuvleyyy		
RULE - SPEICAL CASE EMPTY QUOTES -> EMPTY TOKENS

THIS SPECAIL CASE CAN ONLY HAPPEN IF BEFORE AND AFTER THERE ARE WS (or begiinning / end of string)

all cases can only occure if we are in OUT QOUTE STATE and
and the qoute state changes (found a qoute) 	(index i)
and the previous char is a whitespace		(index i-1) 	(if i=0 ignore this check)
and the next char is a matching qoute 	(index i+1) 	(if i+1 = \0 ignore this check)
and the next next char is a whitespace	(index i+2)	(if i+2 = \0 ignore this check)
	if this fails call recursively

IF the function above fails it only means that we dont create empty tokens. the input could still be valid or invalid
this function doesnt care about it.
 * 
 * @param mbox 
 */
static void empty_quotes(t_mbox *mbox, int i, t_bool check_prev)
{
    int     quote_state;
    char    cur_c;
    t_bool  make_empty;
    
    quote_state = OUT_Q;
    while (mbox->inp_trim[i])
    {
        cur_c = mbox->inp_trim[i];
        update_qoute_state(&quote_state, cur_c, ft_false);
        if (quote_state != OUT_Q)
        {
            make_empty = ft_true;
            if (check_prev && i > 0 && !ft_isspace(mbox->inp_trim[i - 1]))
                make_empty = ft_false;
            if (mbox->inp_trim[i + 1] != quote_state)
                make_empty = ft_false;
            if (mbox->inp_trim[i + 1] && mbox->inp_trim[i + 2]
                && !ft_isspace(mbox->inp_trim[i + 2]))
                {
                    if (ft_isqoute(mbox->inp_trim[i + 2]))  
                        empty_quotes(mbox, i + 2, ft_false);
                    else
                        make_empty = ft_false;
                }
            if (make_empty)
            {
                if (check_prev)
                    mbox->inp_shift[i] = EMPTY_TOKEN;
                else
                    mbox->inp_shift[i] = NO_SPACE;
                mbox->inp_shift[i + 1] = NO_SPACE;
                i++;
                cur_c = mbox->inp_trim[i];
                update_qoute_state(&quote_state, cur_c, ft_false);
            }
        }
        if (!check_prev)
            return ;
        i++;
    }    
}

/**
 * @brief   traverses through the string and if a quotes_state is Q_OUT,
 *          checks if a cur character is one of the separated ones 
 *          and if so it shifts it to negative ASCII values
 * 
 *          context chars:
 *              - context quotes
 *              - whitespaces outside of context quotes
 *              - separators ('|', '<', '>')
 * 
 * @param   mbox 
 * @param   i 
 * @param   quote_state 
 * @return  t_bool 
 */
// TODO: RENAME FUCNTIOn
t_bool  shift_context_chars(t_mbox *mbox, int i, int quote_state)
{
    // first mark empty quotes
    mbox->inp_shift = ft_strdup(mbox->inp_trim);
    // empty_quotes(mbox, 0, ft_true);
    printf ("EMPTY QUOTES \t\t(%s)\n", mbox->inp_shift);
    // exit (0);
    //TODO: use update_wuote_state() because we changed it
    while (mbox->inp_shift[i])
    {
        if(quote_state == OUT_Q && ft_isqoute(mbox->inp_shift[i]))
        {
            if (ft_isqoute(mbox->inp_shift[i + 1])) 
            {
                quote_after_quote(mbox, &i, &quote_state);
                continue ;               
            }
            mbox->inp_shift[i] = add_offset(mbox->inp_shift[i]);
            quote_state = mbox->inp_shift[i];
        }
        else if(quote_state == OUT_Q && ft_issep(mbox->inp_shift[i]))
            mbox->inp_shift[i] = add_offset(mbox->inp_shift[i]);
        else if(quote_state == OUT_Q && ft_isspace(mbox->inp_shift[i]))
            mbox->inp_shift[i] = NO_SPACE;
        else if(quote_state == add_offset(mbox->inp_shift[i]))
        {
            mbox->inp_shift[i] = add_offset(mbox->inp_shift[i]);
            quote_state = OUT_Q;
        }
        i++;
    }
    if (quote_state != OUT_Q)
    {
        create_err_msg("n", "Syntax error: unclosed quotes");
        return (ft_false);
    }
    return (ft_true);
}
