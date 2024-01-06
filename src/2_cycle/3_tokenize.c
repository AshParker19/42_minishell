/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bb_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:14 by anshovah          #+#    #+#             */
/*   Updated: 2024/01/06 18:21:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief   frankenshell creates after modifying the input string
 * 			(e.g. var expansion) a linked list of tokens. The ll is stored in
 * 			mbox->tokens. Each token has a type (enum e_token_type) and a value.
 * 
 * DOCUMENTATION:
 *		https://github.com/ahokcool/frankenshell/docs/documentation.md#tokenizing
 * 
 */

#include "frankenshell.h"     

/**
 * @brief   accepts the substring of the matrix and checks if there is
 * 			an occurence of the shifted version of one of the special
 * 			characters in the string
 * 
 * @param   no_space    
 * @return  t_bool      
 */
static t_bool	check_sp(char *no_space)
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
 * @brief   accepts a not shifted character, shifts it back to a correct
 *          ASCII value and then compares to the separating charactes 
 *          and returns a respective token type (enum e_token_type value)
 * 
 * @param   c           
 * @return  int         
 */
static int	get_token_type(char c)
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
 * @brief   Accepts a string which could contain shifted values and checks if:
 * 				- contains only one char
 * 					- and is a shiffted special char  '|', '<', '>'
 * 						-> shift it back -> return it
 * 					- else
 * 						-> return original character
 * 				- else 
 					remove all the shifted chars hence they are context quotes
 * 
 * @param   str         str to be checked
 * @return  char*       clean string
 */
static	char	*check_shifted_values(char *str)
{
	char	*temp;
	int		i;

	if (!str)
		return (NULL);
	temp = NULL;
	if (ft_strlen(str) == 1 && str[0] < 0)
	{
		if (str[0] == EMPTY_TOKEN)
			temp = ft_calloc(1, sizeof(char));
		else
			temp = ft_chr2str(remove_offset(str[0]));
	}
	else
	{
		i = -1;
		while (str[++i])
			if (str[i] != add_offset('\'') && str[i] != add_offset('"'))
				temp = append_str(temp, ft_chr2str(str[i]), ft_true);
	}
	free (str);
	return (temp);
}

/**
 * @brief   add a new token to the end of tokens linked list
 * 
 * @param   mbox        
 * @param   value       
 * @param   token_type  
 */
static void	add_token(t_mbox *mbox, char *value, int token_type)
{
	t_token	*new_t;
	t_token	*cur;

	new_t = ft_calloc(1, sizeof(t_token));
	if (!new_t)
		return ;
	new_t->type = token_type;
	value = check_shifted_values(value);
	new_t->value = value;
	if (!mbox->tokens)
		mbox->tokens = new_t;
	else
	{
		cur = mbox->tokens;
		while (cur->next)
			cur = cur->next;
		cur->next = new_t;
	}
}

/**
 * @brief	called in a case if input is outside quotes. If the first char is
 * 			a seperator it adds a token with the first char. If not it adds
 * 			a token with the first word.
 * 
 * 			EXAMPLE:
 * 			ls|wc
 * 			the cmd will trigger this function three times:
 * 				1. 	ls
 * 				2. 	|
 * 				3. 	wc
 * 
 * @param	mbox 
 * @param	str 
 * @param	i 
 */
static void	create_next_token_out_quotes(t_mbox *mbox, char *str, int *i)
{
	int	j;

	if (ft_issep(remove_offset(*str)))
	{
		add_token(mbox, ft_substr(str, 0, 1), get_token_type(*str));
		*i = 1;
	}
	else
	{
		j = 0;
		while (str[j])
		{
			if (ft_issep(remove_offset(str[j]))) 
				break ;
			j++;
		}
		*i = j;
		add_token(mbox, ft_substr(str, 0, *i), WORD_TOKEN);
	}
}

/**
 * @brief   receives the substing with a special character between words, 
 * 			splits them into words and characters and adds new tokens 
 * 			to mbox->tokens
 * 
 * @param   mbox        
 * @param   str         
 * @param   i           
 * @param   quote_state 
 */
static void	split_by_sep(t_mbox *mbox, char *str, int i, int quote_state)
{
	while (*str)
	{
		update_quote_state(&quote_state, *str, ft_true);
		if (quote_state == OUT_Q)
		{
			create_next_token_out_quotes(mbox, str, &i);
			str += i;
		}
		else
		{
			i = 0;
			while (str[i])
			{
				if (quote_state == OUT_Q)
					break ;
				update_quote_state(&quote_state, str[i], ft_true);
				i++;
			}
			if (quote_state != OUT_Q)
				add_token(mbox, ft_substr(str, 0, i), get_token_type(*str));
			str += i;
		}
	}
}

/**
 * @brief   This function checks if there is a space between two redir symbols.
 * 			If there is no space between two redir symbols, it prints an error
 * 			and returns false.
 * 
 * 			EXAMPLE:
 * 				if the last char 	of str1 is a >
 * 				and the first chr 	of str2 is a >
 * 				then we have something like "echo hi > > lol"
 * 				-> this is an error so exit cycle
 * 
 * @param   mbox        
 * @param   str1        
 * @param   str2        
 * @return  t_bool      
 */
static t_bool	check_space_between_redir(t_mbox *mbox, char *str1, char *str2)
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
 * @brief   creates a linked list (ll) with tokens generated from
 * 				'mbox->inp_expand'
 * 			the head of the ll will be stored in
 * 				'mbox->tokens'
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/docs/documentation.md#tokenizing
 * 
 * @param   mbox        
 * @param   i           
 * @return  t_bool      
 */
t_bool	tokenize(t_mbox *mbox, int i)
{
	char	**no_space;

	info_put_banner(mbox, "TOKENIZER", NULL, YELLOW);
	no_space = ft_split(mbox->inp_expand, NO_SPACE);
	if (!no_space)
		return (ft_false);
	while (no_space[i])
	{
		if (!check_space_between_redir(mbox, no_space[i], no_space[i + 1]))
		{
			free_whatever("m", no_space);
			return (ft_false);
		}
		if (check_sp(no_space[i]))
			split_by_sep(mbox, no_space[i], 0, OUT_Q);
		else
			add_token(mbox, ft_strdup(no_space[i]), WORD_TOKEN);
		i++;
	}
	free_whatever("m", no_space);
	info_print_tokenizer(mbox, YELLOW);
	if (!mbox->tokens)
		return (ft_false);
	return (ft_true);
}

/**
 * @brief   frees the ll of all tokens if it was allocated
 * 
 * 		NOTE: function should only be called by 'reset_cycle'
 * 
 * @param   mbox        
 */
void	free_tokens(t_mbox *mbox)
{
	t_token	*cur;

	if (!mbox)
		return ;
	while (mbox->tokens)
	{
		cur = mbox->tokens;
		mbox->tokens = mbox->tokens->next;
		if (cur->value)
			free(cur->value);
		free(cur);
	}
	mbox->tokens = NULL;
}