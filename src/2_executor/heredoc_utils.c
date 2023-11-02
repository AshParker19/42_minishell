/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:28:09 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/02 19:29:37 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief   this function gets a string and should return a copied str of the
 *          key. the key will be returned.
 *          
 *          the index i will be shifted!
 * 
 * @param str 
 * @return char* 
 */
char *get_key(t_mbox *mbox, char *str, int *i)
{
    char    *key;

    key = NULL;
    if (!str)
        return (key);
    if (str[*i] == '?')
    {
        
        return (ft_chr2str('?'));
    }
    if (!ft_isalpha(str[(*i)+1]) && str[(*i)+1] != '_')
    {
        (*i)--;
        return(key);
    }
    while(str[*i])
    {
        if (ft_isalnum(str[*i]) || str[*i] == '_')
            key = append_str(key, ft_chr2str(str[*i]), ft_true);
        else
        {
            (*i)--;
            return (key);
        }
        (*i)++;
    }   
    return (key);
}