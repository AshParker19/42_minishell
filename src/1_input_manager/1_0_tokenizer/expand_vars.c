/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/11 10:53:34 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief	this function loops trough a string and sets all characters
 * 			which are whitespaces to NO_SPACE
 * 
 * 			the parameter 'str' will be freed!
 * 
 * @param	str		
 * @return	char*	the string with all spaces marked as NO_SPACE
 */
static	char *mark_ws(char *str)
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
	free(str);
	return(temp);
}


/**
 * @brief 			//TODO: Rename in expand_part
 * 					should search for an key in str
 * 					mbox->inp_shift at postion k.
 * 					at beginnig k points to $ sign!
 * 
 * 					via 'get_key" a key will be found and the index k shiftet
 * 					if found a key
 * 						append expansion via 'append_str' to 'mbox->inp_expand'
 * 					else
 * 						reason can be those:
 * 
 * 					1.dollar is at end of string (Hello$)
 * 						->append the $ sign
 * 					2.$"asd"
 * 					3.for $| or $> or $<
 * 					4.$@lol
 * 
 * @param mbox 
 * @param quote_s 
 * @param k 
 * @param cur_c 
 */
static void found_dollar(t_mbox *mbox, int quote_s, int *k, char cur_c)
{
	char	*key;
	
	(*k)++;
	key = get_key(mbox->inp_shift, k);
	if (key)
		mbox->inp_expand = append_str(mbox->inp_expand,
			get_var_value(mbox, key), ft_false);
	else
	{ // only dollar (end of string)	-> print dollar					Hello$
		(*k)++;
		if (!mbox->inp_shift[*k] || mbox->inp_shift[*k] == '$')
		{
			mbox->inp_expand = append_str(mbox->inp_expand, "$", ft_false);
		}	// $"SMTH"						-> skipp dollar					$"Hi"	//FIXME: << $""''USER"" cat this wont work maybe?
		else if (quote_s == add_offset('"') && mbox->inp_shift[*k] == '\'')
			mbox->inp_expand = append_str(mbox->inp_expand, "$", ft_false);
		//  for $| or $> or $<
		else if (mbox->inp_shift[*k] < 0)
			mbox->inp_expand = append_str(mbox->inp_expand, "$", ft_false);
		// $wrong key					-> skipp dollar and one char	$!LOL
		else if (!ft_isalpha(mbox->inp_shift[*k]) && mbox->inp_shift[*k] != '_')
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
static t_bool detect_heredoc(t_mbox *mbox, int *k, int quote_s, char cur_c)
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
			extract_limiter(mbox, k, &quote_s), ft_true);
		return (ft_true);
	}
	return (ft_false);
}


/*
	traverses through the input string, locates all the variable
	names checking for a dollar sign, then replaces all the variable names
    by their values which are received from the environment

	NEW COMMENT 10.11.2023
	if founda  dollar pasing the index of the dollar to the function
	'found_dollar' this function will deal with the expansion

	'detect_heredoc' this function delals with the a little bit different
	ar xpansion for herdoc limmiter.!
	
*/
t_bool  expand_variables(t_mbox *mbox, int k, int quote_state)
{
    char    cur_c;
    
    mbox->inp_expand = NULL;
    while (mbox->inp_shift[k])
    {
		cur_c = mbox->inp_shift[k];
        update_quote_state(&quote_state, cur_c, ft_true);
		if(!detect_heredoc(mbox, &k, quote_state, cur_c))
		{
			if (quote_state != add_offset('\'') && cur_c == '$') 
                found_dollar(mbox, quote_state, &k, cur_c);
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
