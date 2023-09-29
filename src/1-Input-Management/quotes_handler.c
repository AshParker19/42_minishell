/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/29 16:00:17 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// if((cur_char == IN_SQ || cur_char == IN_DQ) && quote_state == OUT_Q)
//           quote_state = cur_char;
//      else if(quote_state == cur_char)
//          quote_state = OUT_Q;

void update_qoute_state(int *quote_state, char cur_char)
{
    if (*quote_state == OUT_Q) //we
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
            // if(quote_state == '\'')
            //     minibox->input_quoted[i] = IN_SQ;
            // else if(quote_state == '"')
            //     minibox->input_quoted[i] = IN_DQ;
        }
        i++;
    }
    //check if quotes are closed
    if (quote_state != OUT_Q)
    {
        ft_putstr_fd("Syntax error:\n", 2);
        // free_input_strings(minibox);
        // TODO: HERE WE SOMEHOW NEED TO STOP THE INPUT MANAGER
        // MAYBE WITH A RETURN BOOLEAN THAT MARK CONTEXT QUTES FAILED
    }
}

// void	remove_sep_marks(t_minibox *minibox, int i, int j)
// {
//     char    *removed;
//     int     marker_count;

//     marker_count = 0;
//     while (minibox->input_expanded[i])
//     {
//         if (ft_isqoute(remove_offset(minibox->input_expanded[i])))
//             marker_count++;
//         i++;    
//     }
//     printf ("COUNT %d\n", marker_count);
//     removed = ft_calloc(ft_strlen(minibox->input_expanded) - marker_count + 1, 
//         sizeof(char));
//     if (!removed)
//         return ;   
//     i = 0;
//     while (minibox->input_expanded[i])
//     {
//         if (minibox->input_expanded[i] == IN_SQ || minibox->input_expanded[i] == IN_DQ)
//             i++;
//         else
//         {
//             removed[j] = minibox->input_expanded[i];
//             j++;
//             i++;
//         }        
//     }
// }
