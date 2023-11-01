/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:14 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/01 14:56:38 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"     

	
void print_tokens(t_mbox *mbox)
{	
	t_token *current;	
	
	current = mbox->tokens;	
	while (current)	
	{	
		printf ("type:(%d) \t token:(%s)\n", current->type, current->value);	
		current = current->next;	
	}	
}	
	

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
		temp = ft_chr2str(remove_offset(str[0]));
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

/* add a new token to the end of tokens linked list and assigns variables */
static void	add_token(t_mbox *mbox, char *value, int token_type)
{
	t_token	*new_t;
	t_token	*cur;

	new_t = ft_calloc(1, sizeof(t_token));
	if (!new_t)
		return ;
	new_t->type = token_type;
	if (ft_isqoute(value[0]) && ft_isqoute(value[1]))
	{
		free (value);
		new_t->value = ft_calloc(1, sizeof(char));
		if (!new_t->value)
			return ; //TODO: check it in a calling fucntion
	}
	else	
		new_t->value = check_shifted_values(value);
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
/*
	accepts a not shifted character, shifts it back to a correct ASCII value
	and hten compares to the separating charactes and returns a respective
	token type (enum e_token_type value) 
*/
int	get_token_type(char c)
{
	if (remove_offset(c) == '|')
		return (PIPE_TOKEN);
	else if(remove_offset(c) == '<')
		return (RED_IN_TOKEN);
	else if(remove_offset(c) == '>')
		return (RED_OUT_TOKEN);
	return (WORD_TOKEN);		
}

/*
	called in a case if just a sequence of alphanumeric characters without any 
	separators needs to be transformen into a token. uses call by reference
	to update int i in a calling function to shift the string correctly
*/
static void	just_word(t_mbox *mbox, char *str, int *i)
{
	int	j;
	// heloo?????|????wc
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
			// if (ft_issep(remove_offset(str[j]))
			// 	|| ft_isqoute(remove_offset(str[j]))) 
			if (ft_issep(remove_offset(str[j]))) 
				break ;
			j++;
		}
		*i = j;
		add_token(mbox, ft_substr(str, 0, *i), WORD_TOKEN);
	}
}

/*
	receives the substing with a special character between words,
	splits them into words and characters and adds new tokens to mbox->tokens
*/
static void	split_by_sep(t_mbox *mbox, char *str, int i, int quote_state)
{
	while (*str)
	{
		update_qoute_state(&quote_state, *str);
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
				update_qoute_state(&quote_state, str[i]);
				i++;
			}
			if (quote_state != OUT_Q)
				add_token(mbox, ft_substr(str, 0, i), get_token_type(*str));
			str += i;

			// FIXME: JUST CHANGE THAT QOUTES DONT START A NEW TOKEN!
		}
	}
}

void	print_tokenizer_output(t_mbox *mbox)
{
	printf("\n ------------------------------------ \n");
	printf("|           TOKENIZER                |\n");
	printf(" ------------------------------------ \n");
	print_tokens(mbox);
	printf(" ------------------------------------ \n");
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
static t_bool	check_special_case_redir_symbol(char *str1, char *str2)
{
	t_bool	is_correct;

	is_correct = ft_true;
	if (!str1 || !str2)
		return (is_correct);
		
	if (str1[ft_strlen(str1) - 1] == add_offset('>')
		&& str2[0] == add_offset('>'))
	{
		create_error_msg("n", "syntax error near unexpected token `>'");
		is_correct = ft_false;
	}

	if (str1[ft_strlen(str1) - 1] == add_offset('<')
		&& str2[0] == add_offset('<'))
	{
		create_error_msg("n", "syntax error near unexpected token `<'");
		is_correct = ft_false;
	}
	return (is_correct);
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
		if (!check_special_case_redir_symbol(no_space[i], no_space[i+1]))
		{
			free_whatever("m", no_space);
			free_cycle_v2(mbox);
		}
		if (ft_strchr(no_space[i], add_offset('|'))
			|| ft_strchr(no_space[i], add_offset('>'))
			|| ft_strchr(no_space[i], add_offset('<'))
			|| ft_strchr(no_space[i], add_offset('\''))
			|| ft_strchr(no_space[i], add_offset('"')))
		{
			split_by_sep(mbox, no_space[i], 0, OUT_Q);
		}
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
