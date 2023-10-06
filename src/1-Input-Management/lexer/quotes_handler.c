/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/05 19:20:26 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
    accepts an address of quote_state to update it using call by reference
    and accepts the current char of yhe srting. checks the current quote state
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
    checks if a current character is one of the separated ones 
    and if so it shifts it to negative ASCII values
*/
void	mark_seps(t_minibox *minibox, int i, int quote_state)
{
    minibox->input_quoted = ft_strdup(minibox->input_trimmed);
    while (minibox->input_quoted[i])
    {
        if(quote_state == OUT_Q && ft_isqoute(minibox->input_quoted[i]))
        {
            minibox->input_quoted[i] = add_offset(minibox->input_quoted[i]);
            quote_state = minibox->input_quoted[i];
        }
        else if(quote_state == OUT_Q && ft_issep(minibox->input_quoted[i]))
            minibox->input_quoted[i] = add_offset(minibox->input_quoted[i]);
        else if(quote_state == OUT_Q && ft_isspace(minibox->input_quoted[i]))
            minibox->input_quoted[i] = NO_SPACE;
        else if(quote_state == add_offset(minibox->input_quoted[i]))
        {
            minibox->input_quoted[i] = add_offset(minibox->input_quoted[i]);
            quote_state = OUT_Q;
        }
        i++;
    }
    //check if quotes are closed
    if (quote_state != OUT_Q)
    {
        ft_putstr_fd("Syntax error:\n", 2);
        // exit(0); FIXME:
        // free_input_strings(minibox);
        // TODO: HERE WE SOMEHOW NEED TO STOP THE INPUT MANAGER
        // MAYBE WITH A RETURN BOOLEAN THAT MARK CONTEXT QUTES FAILED
    }
}
