/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:28:09 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/04 18:45:06 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	this function will be only called by 'heredoc' for each line
 * 			if the heredoc recieves CRTL+D (EOF) => !line  it will print the 
 * 			responding error message and exit the heredoc child process properly
 * 			with exit status SUCCESS via 'exit_heredoc_child'
 * 
 * @param	mbox 
 * @param	fd 
 * @param	lim 
 * @param	line 
 */
void	check_ctrl_d(t_mbox *mbox, int *fd, char *lim, char *line)
{
	if (!line)
	{
		err_msg(mbox, NO_EXIT_STATUS, "nnynnn", ERR_P,
			W_HD, ft_itoa(mbox->count_cycles), DW, lim, "')");
		exit_heredoc_child(mbox, fd, lim, line, EXIT_SUCCESS);
	}
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
 * @param	mbox 
 * @param	fd 
 * @param	lim 
 * @param	line 
 */
void	exit_heredoc_child(t_mbox *mbox, int *fd, char *lim, char *line, int exit_status)
{
	close(fd[P_LEFT]); // close because it was WRITE END
	free_whatever("pp", lim, line);
	set_var_value_int(mbox, "?", exit_status);
	close_process_fds_v2(mbox);
	free_and_close_box_v2(mbox);
}
