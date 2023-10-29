/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:05:22 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/28 23:14:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	shifts the receiving character to negative ASCII values
 * 			so it will be used for tokenization
 * 
 * @param	c 
 * @return	int 
 */
int	add_offset(int c)
{
	return (c - 126);
}

/**
 * @brief	shifts it back to a needed ASCII value
 * 
 * @param	c 
 * @return	int 
 */
int	remove_offset(int c)
{
	return (c + 126);
}

/**
 * @brief these functions return true or false depending on the result of checking:
 * 
 */
/* if the receiving character is single or double quote */
t_bool	ft_isqoute(char c)
{
	return (c == '\'' || c == '"');
}

/* if it is one of the separators */
t_bool	ft_issep(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

/* if it is one of the whitespaces */
t_bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\a'
		|| c == '\b' || c == '\f' || c == '\r');
}

/**
 * @brief	frees the ll of all tokens if it was allocated
 * 			
 * 			NOTE: function should only be called by 'free_cycle'
 * 
 * @param mbox 
 */
void free_tokens_v2(t_mbox *mbox)
{
	t_token *cur;

	while(mbox->tokens)
	{
		cur = mbox->tokens;
		mbox->tokens = mbox->tokens->next;
		free(cur->value);
		free(cur);
	}
	mbox->tokens = NULL;
}
