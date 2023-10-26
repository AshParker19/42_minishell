/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:45:25 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/26 19:20:19 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief   This function treats those special case:
 *              << $'USER'          ->LIM: USER
 *              << $"USER"          ->LIM: USER
 *              << $"USER"$"USER"    ->LIM: USERUSER
 * 
 * @param lim 
 * @return char* 
 */

// 0123456i
// "hello$"" ;akdsjds f"

// 0i
// $"lol"

// << $"USER"$"USER"$"USER"
// << "USER"$"USER"$"USER"

// << "USER""USER""USER"
static  char *treat_case_dollar(char *lim)
{
    int     i;
    char    *temp;
    char    *left; 
    char    *right;
    t_bool  found_dollar;

    i = -1;
    found_dollar = ft_false;
    temp = NULL;
    while (lim[++i])
    {
        if (lim[i] == '$')
            found_dollar = ft_true;
        else if (found_dollar && (lim[i] == '\'' || lim[i] == '"'))
            {
                left = ft_substr(lim, 0, i-1);
                right = ft_strdup(&lim[i]);
                printf("(%s)(%s)\n", left, right);
                temp = treat_case_dollar(ft_strcat_multi(2, left, right));
                free_whatever("pp", left, right);
                return(temp);
                found_dollar = ft_false;
            }
        else
            found_dollar = ft_false;
        
    }    
    return (lim);
}

/**
 * @brief the k when calling the function will ppoint to the 2nd <
 * 
 * @param minibox 
 * @return char* 
 */
char *extract_limiter(t_minibox *minibox, int *k, int *quote_state)
{
    char    cur_char;
    char    *lim;
    t_bool  lim_start;

    lim = NULL;
    lim_start = ft_false;
    (*k)++;
    while (minibox->input_quoted[*k])
    {
        cur_char = minibox->input_quoted[*k];
        update_qoute_state(quote_state, cur_char);
        // printf("FIND LIMITER: k (%d) CUR CHAR (%c) CUR QOUTE STATE(%d)\n", *k, cur_char, *quote_state);
        if (cur_char != NO_SPACE)
            lim_start = ft_true;
        if (lim_start)
        {
            if (cur_char < 0)
                cur_char = remove_offset(cur_char);
            if (*quote_state == OUT_Q)
                if (ft_issep(cur_char) || add_offset(cur_char) == NO_SPACE)
                    break ;
            lim = append_str(lim, ft_chr2str(cur_char),ft_true);
        }
        (*k)++;
    }
    // printf("---\nTHIS IS OUR LIM BEFORE TREATING $\": (%s)\n", lim);
    lim = treat_case_dollar(lim);
    // printf("---\nTHIS IS OUR LIM: (%s)\n", lim);
    (*k)--;
    return (lim);
}


//  << hi$LESSho cat | echo $LESS