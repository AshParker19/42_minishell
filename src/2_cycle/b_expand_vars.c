/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_expand_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/18 19:46:54 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief	this function loops trough a string and sets all characters
 * 			which are whitespaces to NO_SPACE
 * 
 * @param	str		
 * @return	char*	the string with all spaces marked as NO_SPACE
 */
static char	*mark_ws(char *str)
{
	int		i;
	char	*temp;

	if (!str)
		return (NULL);
	temp = NULL;
	i = -1;
	while (str[++i])
	{
		if (ft_isspace(str[i]))
			temp = append_str(temp, ft_chr2str(NO_SPACE), ft_true);
		else
			temp = append_str(temp, ft_chr2str(str[i]), ft_true);
	}
	return (temp);
}

/**
 * @brief 			
 * 					should search for an key in str
 * 					mbox->inp_shift at postion k.
 * 					at beginnig k points to '$' char!
 * 
 * 					via 'get_key" a key will be found and the index k shiftet
 * 					if found a key
 * 						whitespaces will be replaced by NO_SPACE
 * 						append str via 'append_str' to 'mbox->inp_expand'
 * 					else
 * 						reason can be one of those:
 * 
 * 		1. dollar is at end of string 'Hello$'	-> append the '$' str)
 * 		1. inside quotes						-> append the '$' str)
 * 		2. $"SMTH" or $'SMTH'					-> skipp dollar
 * 		3. for $| or $> or $<					-> append the '$' str)
 * 		4. $@lol								-> skipp dollar
 * 
 * @param mbox 
 * @param quote_s 
 * @param k 
 * @param cur_c 
 */
static void	expand_var(t_mbox *mbox, int quote_s, int *k)
{
	char	*key;
	char	temp;

	(*k)++;
	key = get_key(mbox->inp_shift, k);
	if (key)
		mbox->inp_expand = append_str(mbox->inp_expand,
				mark_ws(get_var_value(mbox, key)), ft_true);
	else
	{
		(*k)++;
		temp = mbox->inp_shift[*k]; 
		if (!temp || temp == '$' || quote_s != OUT_Q)
			mbox->inp_expand = append_str(mbox->inp_expand, "$", ft_false);
		else if ((temp == add_offset('"') || temp == add_offset('\'')))
			(*k)++;
		else if (temp < 0
			&& !(temp == add_offset('"') || temp == add_offset('\'')))
			mbox->inp_expand = append_str(mbox->inp_expand, "$", ft_false);
		else if (!ft_isalpha(temp) && temp != '_')
			(*k)++;
		(*k)--;
	}
	free(key);
}

/**
 * @brief	counts the occurens of < symbols
 * 			if two in a row the next thing will be the lummiter
 * 			since the lim has a special expansion it will be dealt with here
 * 
 * @param	mbox 
 * @param	k 
 * @param	quote_s 
 * @param	cur_c 
 * @return	t_bool 
 */
static t_bool	detect_heredoc(t_mbox *mbox, int *k, int quote_s, char cur_c)
{
	if (quote_s == OUT_Q)
	{
		if (remove_offset(cur_c) == '<')
			mbox->consecutive_lt++;
		else
			mbox->consecutive_lt = 0;
	}
	if (mbox->consecutive_lt == 2)
	{
		mbox->inp_expand = append_str(mbox->inp_expand,
				ft_chr2str(cur_c), ft_true);
		mbox->inp_expand = append_str(mbox->inp_expand,
				extract_limiter(mbox, k, &quote_s, NULL), ft_true);
		return (ft_true);
	}
	return (ft_false);
}

/**
 * @brief   This function gets a string and should return a copied str of the
 *          key. the key will be returned.
 * 
 * 			NOTE:         
 *          the index i will be shifted!
 * 
 * 			regex key:
 * 				^[a-zA-Z_]+[a-zA-Z0-9_]*$
 * 
 * 				^			-> start of string
 * 				[a-zA-Z_]	-> first char must be a letter or '_'
 * 				+			-> one or more
 * 				[a-zA-Z0-9_]*-> zero or more letters, numbers or '_'
 * 
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
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#environment-variables
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

/*
	traverses through the input string, locates all the variable
	names checking for a dollar sign, then replaces all the variable names
	by their values which are received from the environment

	NEW COMMENT 10.11.2023
	if founda  dollar pasing the index of the dollar to the function
	'expand_var' this function will deal with the expansion

	'detect_heredoc' this function delals with the a little bit different
	ar xpansion for herdoc limmiter.!
	
*/
t_bool	expand_vars_main(t_mbox *mbox, int k, int quote_state)
{
	char	cur_c;

	mbox->inp_expand = NULL;
	while (mbox->inp_shift[k])
	{
		cur_c = mbox->inp_shift[k];
		update_quote_state(&quote_state, cur_c, ft_true);
		if (!detect_heredoc(mbox, &k, quote_state, cur_c))
		{
			if (quote_state != add_offset('\'') && cur_c == '$') 
				expand_var(mbox, quote_state, &k);
			else
				mbox->inp_expand = append_str(mbox->inp_expand,
						ft_chr2str(cur_c), ft_true);
		}
		k++;
	}
	if (!mbox->inp_expand || mbox->inp_expand[0] == '\0')
		return (ft_false);
	return (ft_true);
}
