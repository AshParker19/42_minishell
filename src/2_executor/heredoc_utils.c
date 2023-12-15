/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:28:09 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/15 14:16:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

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
char	*get_key(char *str, int *i)
{
	char	*key;

	key = NULL;
	if (!str)
		return (key);
	if (str[*i] == '?')
		return (ft_chr2str('?'));
	if (!ft_isalpha(str[(*i)]) && str[(*i)] != '_')
	{
		(*i)--;
		return (key);
	}
	while (str[*i])
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

/**
 * @brief	will be called to properly end the heredoc child process
 * 
 * 
 * 	close(hd->fd[P_LEFT]); // close because it was WRITE END
 * 
 * @param	mbox 
 * @param	fd 
 * @param	lim 
 * @param	line 
 */
void	exit_heredoc_child(t_mbox *mbox, t_hd *hd, int exit_status)
{
	close(hd->fd[P_LEFT]);
	free_whatever("pp", hd->lim, hd->cur_line);
	set_var_value_int(mbox, "?", exit_status);
	close_process_fds_v2(mbox);
	destroy_mbox(mbox);
}
