/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:19:11 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/22 09:52:57 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	accepts the substring of the matrix and checks if there is
 * 			an occurence of the shifted version of one of the special
 * 			characters in the string
 * 			
 * 			returns corresponding t_bool value
 * @param	no_space 
 * @return	t_bool 
 */
t_bool	check_sp(char *no_space)
{
	if (ft_strchr(no_space, add_offset('|'))
		|| ft_strchr(no_space, add_offset('>'))
		|| ft_strchr(no_space, add_offset('<'))
		|| ft_strchr(no_space, add_offset('\''))
		|| ft_strchr(no_space, add_offset('"')))
	{
		return (ft_true);
	}
	return (ft_false);
}

/**
 * @brief	cheeck spreadsheet!
 * 			if the last char 	of str1 is a >
 * 			and the first chr 	of str2 is a >
 * 			then we have something like "echo hi > > lol"
 * 			-> this is an error so exit cycle
 * 
 * @return t_bool 
 */
t_bool	check_space_between_redir(t_mbox *mbox, char *str1, char *str2)
{
	t_bool	is_correct;

	is_correct = ft_true;
	if (!str1 || !str2)
		return (is_correct);
	if (str1[ft_strlen(str1) - 1] == add_offset('>')
		&& str2[0] == add_offset('>'))
	{
		err_msg(mbox, 2, "nn", ERR_P, SE_GT);
		is_correct = ft_false;
	}
	if (str1[ft_strlen(str1) - 1] == add_offset('<')
		&& str2[0] == add_offset('<'))
	{
		err_msg(mbox, 2, "nn", ERR_P, SE_LT);
		is_correct = ft_false;
	}
	return (is_correct);
}

/**
 * @brief   accepts a not shifted character, shifts it back to a correct
 *          ASCII value and hten compares to the separating charactes 
 *          and returns a respective token type (enum e_token_type value)
 * 
 * @param   c 
 * @return  int 
 */
int	get_token_type(char c)
{
	if (remove_offset(c) == '|')
		return (PIPE_TOKEN);
	else if (remove_offset(c) == '<')
		return (RED_IN_TOKEN);
	else if (remove_offset(c) == '>')
		return (RED_OUT_TOKEN);
	return (WORD_TOKEN);
}

/**
 * @brief	frees the ll of all tokens if it was allocated
 * 			
 * 			NOTE: function should only be called by 'free_cycle'
 * 
 * @param   mbox 
 */
void	free_tokens_v2(t_mbox *mbox)
{
	t_token	*cur;

	while (mbox->tokens)
	{
		cur = mbox->tokens;
		mbox->tokens = mbox->tokens->next;
		free(cur->value);
		free(cur);
	}
	mbox->tokens = NULL;
}
