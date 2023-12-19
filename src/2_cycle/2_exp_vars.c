/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_exp_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/19 19:31:52 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   This function loops trough a string and replaces all whitespace
 * 			characters with the flag NO_SPACE.
 * 
 * 
 * 			This is needed fo the variable expansion. The variable expansion
 * 			needs to replace all whitespaces inside the value of the variable
 * 			with the flag NO_SPACE, so that the tokenizer can later on create
 * 			the multiple / correct tokens.
 * 
 * 			NOTE:
 * 			The quote state is not considered here!
 * 
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#removal-of-whitespaces-of-expanded-variable-values
 * 
 * @param   str         
 * @return  char*       
 */
static char	*shift_ws(char *str)
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
 * @brief   Here the actual expansion of the variable happens.
 * 			This function is called if the quote state is not in single quotes
 * 			and a dollar sign is found. So at index k the dollar sign is found.
 * 
 * How its works:
 * 	- if a valid key can be extracted via 'get_key'
 * 		- the value will found with 'get_var_value'
 * 		- all whitespaces will be replaced with NO_SPACE via 'shift_ws'
 * 		- the expanded value will be appended to 'inp_expand'
 * 	- else
 * 		append the dollar sign to 'inp_expand' if:
 * 			- the $ is at the end of the string 			(e.g. Hello$)
 * 			- the next char is a seperator 					(e.g. $|, $>, $<)
 * 			- the next char is a dollar sign as well 		(e.g. $$$) 
 * 			- the next char closes context double quotes	(e.g. "foo$")
 * 		DONT'T append the dollar sign to 'inp_expand' if
 * 		- the next char is a quote 							(e.g. $"foo")
 * 		- the key is wrong 									(e.g. $@foo)
 * 
 * @param   mbox        
 * @param   quote_s     
 * @param   k           
 */
static void	expand_var(t_mbox *mbox, int quote_s, int *k)
{
	char	*key;
	char	temp;

	(*k)++;
	key = get_key(mbox->inp_shift, k);
	if (key)
		mbox->inp_expand = append_str(mbox->inp_expand,
				shift_ws(get_var_value(mbox, key)), ft_true);
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
 * @brief   This recursive function treats those special cases to remove the
 * 			dollar sign from the lim of a hd if followed by contextual quotes.
 *              << $'USER'           ->LIM: 'USER'
 *              << $"USER"           ->LIM: "USER"
 *              << $"USER"$"USER"    ->LIM: "USER""USER"
 * 
 * 			NOTE: The contextual quotes will be removed later on in the hd
 * 			handling itself.
 * 
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#extract-limiter
 * 
 * @param   lim         
 * @param   i           
 * @param   temp        
 * @return  char*       
 */
static char	*hd_lim_case_dollar(char *lim, int i, char *temp)
{
	char	*left; 
	char	*right;
	t_bool	found_dollar;

	if (!lim)
		return (NULL);
	found_dollar = ft_false;
	while (lim[++i])
	{
		if (lim[i] == '$')
			found_dollar = ft_true;
		else if (found_dollar && (lim[i] == '\'' || lim[i] == '"'))
		{
			left = ft_substr(lim, 0, i - 1);
			right = ft_strdup(&lim[i]);
			temp = hd_lim_case_dollar(ft_strcat_multi(2, left, right), -1, NULL);
			free_whatever("ppp", left, right, lim);
			return (temp);
			found_dollar = ft_false;
		}
		else
			found_dollar = ft_false;
	}
	return (lim);
}
/**
 * @brief   This function is called if while traversing through the input string
 * 			two consecutive `<` are found. This means that the next word needs
 * 			to be the hd limiter. This function extracts the limiter by:
 * 				- traversing through the string to extract limiter
 *	 				- skipping all whitespaces in the beginning
 * 					- shifting chars back to positive ASCII
 * 					- if quote state is OUT_Q and cur_char is a seperator
 * 						- break
 * 				- checking dollar signs in limiter via 'hd_lim_case_dollar'
 * 
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#extract-limiter
 * 
 * @param   mbox		
 * @param   k           
 * @param   quote_state 
 * @param   lim         
 * @return  char*       
 */
static char	*get_hd_lim(t_mbox *mbox, int *k, int *quote_state, char *lim)
{
	char	cur_char;
	t_bool	lim_start;

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
	lim = hd_lim_case_dollar(lim, -1, NULL);
	(*k)--;
	return (lim);
}

/**
 * @brief	Counts the occurens of < symbols in a row
 * 			Therefore it uses the variable `consecutive_lt` in `mbox`
 *
 * 			If two `<` will be found the next word needs to be the hd limiter.
 * 			Since the lim has a special expansion the function `get_hd_lim`
 * 			will be called and the index k will be shifted to the end of the
 * 			limiter.
 * 
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#extract-limiter
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
				get_hd_lim(mbox, k, &quote_s, NULL), ft_true);
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
 * @param   str         
 * @param   i           
 * @return  char*       
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
 * @brief   This function expands all the env variables in the input string
 * 			`inp_shift` -> `inp_expand`
 * 
 * 			Therefore it:
 *				- traverses through `inp_shift`
 *					- updates the quote state
 *					- if special case heredoc
 *						- function 'detect_heredoc' (appends to `inp_expand`)
 *					- else if not in single quotes and dollar sign is found
 *						- function 'expand_var' -> expansion
 *						- append expanded var to `inp_expand`
 *					- else (normal char)
 *						- append char to `inp_expand`
 * 
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#variable-expansion
 * 
 * @param   mbox        
 * @param   k           
 * @param   quote_state 
 * @return  t_bool      
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
