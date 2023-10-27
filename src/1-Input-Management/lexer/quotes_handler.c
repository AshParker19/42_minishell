/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/27 15:14:01 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
    accepts an address of quote_state to update it using call by reference
    and accepts the cur char of yhe srting. checks the cur quote state
    and compares it to single or double quotes characters.
    if quote_state is OUT_Q, means no quote were found before and is it is now
        change quote state to aacording value(single or double quote)
    else means that the quote was found, and is a needed quote occurs
        close it and put quote_state to OUT_Q     
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
/*
    traverses through the string and if a quotes_state is Q_OUT,
    checks if a cur character is one of the separated ones 
    and if so it shifts it to negative ASCII values
*/
void	mark_seps(t_mbox *mbox, int i, int quote_state)
{
    mbox->inp_shift = ft_strdup(mbox->inp_trim);
    while (mbox->inp_shift[i])
    {
        if(quote_state == OUT_Q && ft_isqoute(mbox->inp_shift[i]))
        {
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
    //check if quotes are closed
    if (quote_state != OUT_Q)
    {
        ft_putstr_fd("Syntax error:\n", 2);
        // exit(0); FIXME:
        // free_input_strings(mbox);
        // TODO: HERE WE SOMEHOW NEED TO STOP THE INPUT MANAGER
        // MAYBE WITH A RETURN BOOLEAN THAT MARK CONTEXT QUTES FAILED
    }
}
