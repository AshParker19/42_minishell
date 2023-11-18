/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:14 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/18 16:34:34 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"     
	
/**
 * @brief	accepts a string which could contain shifted values and cheks if:
 * 				- contains only one char
 * 					- and is a shiffted special char  '|', '<', '>'
 * 						-> shift it back -> return it
 * 					- else
 * 						-> return original character
 * 				- else 
 					remove all the shifted chars hence they are context quotes
 * 
 * @param	str		str to be checked
 * @return	char* 	clean string
 */
static	char	*check_shifted_values(char *str)
{
	char 	*temp;
	int		i;
	
	if (!str)
		return (NULL);
	temp = NULL;
	if (ft_strlen(str) == 1 && str[0] < 0)
	{
		if (str[0] == EMPTY_TOKEN)
			temp = ft_calloc(1, sizeof(char));//TODO: check it in a calling fucntion(we need to afree the allocated part of the list if it crashed) MALLOC PROTECION -> wait fo libfts ll functions, this we then can call!
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

// /* add a new token to the end of tokens linked list and assigns variables */
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
 * @brief	called in a case if just a sequence of alphanumeric characters
 * 			without any separators needs to be transformen into a token.
 * 			uses call by reference to update int i in a calling function
 * 			to shift the string correctly
 * 
 * @param	mbox 
 * @param	str 
 * @param	i 
 */
static void	just_word(t_mbox *mbox, char *str, int *i)
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
 * @brief	receives the substing with a special character between words, 
 * 			splits them into words and characters and adds new tokens 
 * 			to mbox->tokens
 * 
 * @param	mbox 
 * @param	str 
 * @param	i 
 * @param	quote_state 
 */
static void	split_by_sep(t_mbox *mbox, char *str, int i, int quote_state)
{
	while (*str)
	{
		update_quote_state(&quote_state, *str, ft_true);
		if (quote_state == OUT_Q)
		{
			just_word(mbox, str, &i);
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
 * @brief	creates a linked list (ll) with tokens generated from
 * 				'mbox->inp_expand'
 * 			the head of the ll will be stored in
 * 				'mbox->tokens'
 * 
 * 			RULE:
 * 
 *			NOTE:	- contextual qoutes and seperators ('|', '<', '>')
 						will be neg ascii values; here represeted by '?'
					- tokens will be seperated by ';'
 * 			EXAMPLES: 
 * 				(echo ?HELLO WORLD?)	->	(echo;Hello World;)
 * 	
 * @param mbox 
 * @param i 
 */
t_bool	tokenize(t_mbox *mbox, int i)
{
	char	**no_space;

	no_space = ft_split(mbox->inp_expand, NO_SPACE);
	while (no_space[i])
	{
		if (!check_space_between_redir(mbox, no_space[i], no_space[i+1]))
		{
			free_whatever("m", no_space);
			free_cycle_v2(mbox);
			return (ft_false);
		}
		if (check_sp(no_space[i]))
			split_by_sep(mbox, no_space[i], 0, OUT_Q);
		else
			add_token(mbox, ft_strdup(no_space[i]), WORD_TOKEN);
		i++;
	}
	free_whatever("m", no_space);
	print_tokenizer_output(mbox);
	if (!mbox->tokens)
		return (ft_false); //TODO: check return values of all the funcs and check if the list didnt fail in the middle
	return (ft_true);	
}

