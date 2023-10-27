/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:14 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/27 15:14:01 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_mbox *mbox)
{
	t_token	*cur;

	cur = mbox->tokens;
	while (cur)
	{
		printf ("type:(%d) \t token:(%s)\n", cur->type, cur->value);
		cur = cur->next;
	}
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
	if (value[0] < 0)
	{
		new_t->value = ft_calloc(2, sizeof(char));
		new_t->value[0] = remove_offset(value[0]);
		free(value);
	}
	else
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
			if (ft_issep(remove_offset(str[j]))
				|| ft_isqoute(remove_offset(str[j]))) 
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

/*
	makes a linked list with the tokens grabbed from 
	mbox->inp_expand
	the result will be stored in the linked list:
	mbox->tokens
*/
void	tokenize(t_mbox *mbox, int i)
{
	char	**no_space;

	no_space = ft_split(mbox->inp_expand, NO_SPACE);
	while (no_space[i])
	{
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
}
