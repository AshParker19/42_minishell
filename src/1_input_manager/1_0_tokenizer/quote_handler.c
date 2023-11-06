/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/06 11:03:03 by anshovah         ###   ########.fr       */
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
void update_qoute_state(int *quote_state, char cur_char)
{
    if (*quote_state == OUT_Q)
    {
        if (cur_char == add_offset('\''))
            *quote_state = cur_char;
        else if (cur_char == add_offset('"'))
            *quote_state = cur_char;
    }
    else if (*quote_state == add_offset('\''))
    {
        if (cur_char == add_offset('\''))
            *quote_state = OUT_Q;
    }
    else if (*quote_state == add_offset('"'))
    {
        if (cur_char == add_offset('"'))
            *quote_state = OUT_Q;
    }
}

static void   quote_after_quote(t_mbox *mbox, int *i, int *quote_state)
{
    char    prev_quote;
    int     j;

    prev_quote = mbox->inp_shift[*i];
        // if (mbox->inp_shift[i + 1] != prev_quote)
            // {
            //     create_error_msg("nnnnn", ERR_PROMT, "syntax error: unexpected unpaired ", ft_chr2str('"'),
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

/**
 * @brief   traverses through the string and if a quotes_state is Q_OUT,
 *          checks if a cur character is one of the separated ones 
 *          and if so it shifts it to negative ASCII values
 * 
 * @param   mbox 
 * @param   i 
 * @param   quote_state 
 * @return  t_bool 
 */
// TODO: RENAME FUCNTIOn
t_bool  mark_seps(t_mbox *mbox, int i, int quote_state)
{
    mbox->inp_shift = ft_strdup(mbox->inp_trim);
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
        create_error_msg("n", "Syntax error: unclosed quotes");
        return (ft_false);
    }
    return (ft_true);
}
