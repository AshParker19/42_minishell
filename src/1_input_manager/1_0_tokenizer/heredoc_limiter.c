/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_limiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:45:25 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/09 20:48:10 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief   This function treats those special cases:
 *              << $'USER'           ->LIM: USER
 *              << $"USER"           ->LIM: USER
 *              << $"USER"$"USER"    ->LIM: USERUSER
 * 
 * @param lim 
 * @return char* 
 */
static  char *treat_case_dollar(char *lim)
{
    int     i;
    char    *temp;
    char    *left; 
    char    *right;
    t_bool  found_dollar;

    if (!lim)
        return (NULL);
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
            temp = treat_case_dollar(ft_strcat_multi(2, left, right));
            free_whatever("ppp", left, right, lim);
            return(temp);
            found_dollar = ft_false;
        }
        else
            found_dollar = ft_false;    
    }    
    return (lim);
}

/**
 * @brief the k when calling the function will point to the 2nd < ???????
 * 
 * @param mbox 
 * @return char* 
 */
char *extract_limiter(t_mbox *mbox, int *k, int *quote_state)
{
    char    cur_char;
    char    *lim;
    t_bool  lim_start;

    lim = NULL;
    lim_start = ft_false;
    (*k)++;
    while (mbox->inp_shift[*k])
    {
        cur_char = mbox->inp_shift[*k];
        update_quote_state(quote_state, cur_char, ft_true);
        if (cur_char != NO_SPACE)
            lim_start = ft_true;
        if (lim_start)
        {
            if (cur_char < 0)
                cur_char = remove_offset(cur_char);
            if (*quote_state == OUT_Q)
                if (ft_issep(cur_char) || add_offset(cur_char) == NO_SPACE)
                    break ;
            lim = append_str(lim, ft_chr2str(cur_char), ft_true);
        }
        (*k)++;
    }
    lim = treat_case_dollar(lim);
    (*k)--;
    return (lim);
}
