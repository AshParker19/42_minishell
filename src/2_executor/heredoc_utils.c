/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:28:09 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/10 17:07:41 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief	normally we just pass the mbo to all functions.
 * 			in the case of signals in heredoc we cant!
 * 			therefore we have this fucntion
 * 			USAGE:
 * 				In main we call it once like
 * 					get_mbox(mbox);
 * 				this will set the static var to our mbox
 *
 * 				In signal handler we juts call it like
 * 					get_mbox(NULL);
 * 				this will return the pointer to mbox
 *
 * @param mbox
 * @return t_mbox*
 */
t_mbox	*get_mbox(t_mbox *mbox)
{
	static t_mbox	*mbox_ptr;

	if (mbox)
		mbox_ptr = mbox;
	return (mbox_ptr);
}

/**
 * @brief   this function gets a string and should return a copied str of the
 *          key. the key will be returned.
 *          
 *          the index i will be shifted!
 * 
 * 			EXAMPLE:
 * 			i	str				RETURN		i (new)
 * 			-----------------------------------------
 * 			1	$LESS Hello	-> LESS			4
 * 			1	$@ Hello	-> NULL			0
 * 			1	$"Hi"		-> NULL			0
 * 			3	HI$LESS		-> LESS			6
 * 			3	HI$LESS@lol	-> LESS			6
 * 
 * @param	str 
 * @return	char* 
 */
char *get_key(char *str, int *i)
{
    char    *key;
    key = NULL;
    if (!str)
        return (key);
    if (str[*i] == '?')
        return (ft_chr2str('?'));
    if (!ft_isalpha(str[(*i)]) && str[(*i)] != '_')
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
	(*i)--;
    return (key);
}
