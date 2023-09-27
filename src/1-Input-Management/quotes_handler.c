/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:59 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/27 09:18:24 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	mark_context_quotes(t_minibox *minibox, int i, int quote_state)
{
    minibox->input_quoted = ft_strdup(minibox->input_trimmed);
    while (minibox->input_quoted[i])
    {
        if(minibox->input_quoted[i] == '\'' && quote_state == OUT_Q)
        {
            quote_state = minibox->input_quoted[i];
            minibox->input_quoted[i] = IN_SQ;
        }
        else if (minibox->input_quoted[i] == '"' && quote_state == OUT_Q)
        {
            quote_state = minibox->input_quoted[i];
            minibox->input_quoted[i] = IN_DQ;
        }
        else if(quote_state == minibox->input_quoted[i])
        {
            if(quote_state == '\'')
                minibox->input_quoted[i] = IN_SQ;
            else if(quote_state == '"')
                minibox->input_quoted[i] = IN_DQ;
            quote_state = OUT_Q;
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

void	remove_context_quotes(t_minibox *minibox, int i, int j)
{
    char    *removed;
    int     marker_count;

    marker_count = 0;
    while (minibox->input_expanded[i])
    {
        if (minibox->input_expanded[i] == IN_SQ || minibox->input_expanded[i] == IN_DQ)
            marker_count++;
        i++;    
    }
    removed = ft_calloc(ft_strlen(minibox->input_expanded) - marker_count + 1, 
        sizeof(char));
    if (!removed)
        return ;   
    i = 0;
    while (minibox->input_expanded[i])
    {
        if (minibox->input_expanded[i] == IN_SQ || minibox->input_expanded[i] == IN_DQ)
            i++;
        else
        {
            removed[j] = minibox->input_expanded[i];
            j++;
            i++;
        }        
    }
}
