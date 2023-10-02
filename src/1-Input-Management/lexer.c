/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:14 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/02 15:25:53 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_minibox *minibox)
{
	t_token	*current;

	current = minibox->tokens;
	printf("START PRINTING\n---\n");
	while (current)
	{
		printf ("type:(%d) \t token:╟%s╢\n", current->type, current->value);
		current = current->next;
	}
	printf("---\nEND PRINTING\n");
}

/* add a new token to the end of tokens linked list and assigns variables */
static void	add_token(t_minibox *minibox, char *value, int token_type)
{
	t_token	*new_t;
	t_token	*current;

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
	if (!minibox->tokens)
		minibox->tokens = new_t;
	else
	{
		current = minibox->tokens;
		while (current->next)
			current = current->next;
		current->next = new_t;
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
static void	just_word(t_minibox *minibox, char *str, int *i)
{
	int	j;

	if (ft_issep(remove_offset(*str)))
	{
		add_token(minibox, ft_substr(str, 0, 1), get_token_type(*str));
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
		add_token(minibox, ft_substr(str, 0, *i), WORD_TOKEN);
	}
}

/*
	receives the substing with a special character between words,
	splits them into words and characters and adds new tokens to minibox->tokens
*/
static void	split_by_sep(t_minibox *minibox, char *str, int i, int quote_state)
{
	while (*str)
	{
		update_qoute_state(&quote_state, *str);
		if (quote_state == OUT_Q)
		{
			just_word(minibox, str, &i);
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
				add_token(minibox, ft_substr(str, 0, i), get_token_type(*str));
			str += i;
		}
	}
}

/*
	makes a linked list with the tokens grabbed from 
	minibox->input_expaned
	the result will be stored in the linked list:
	minibox->tokens
*/
void	tokenize(t_minibox *minibox, int i)
{
	char	**no_space;

	no_space = ft_split(minibox->input_expanded, NO_SPACE);
	while (no_space[i])
	{
		if (ft_strchr(no_space[i], add_offset('|'))
			|| ft_strchr(no_space[i], add_offset('>'))
			|| ft_strchr(no_space[i], add_offset('<'))
			|| ft_strchr(no_space[i], add_offset('\''))
			|| ft_strchr(no_space[i], add_offset('"')))
		{
			split_by_sep(minibox, no_space[i], 0, OUT_Q);
		}
		else
			add_token(minibox, ft_strdup(no_space[i]), WORD_TOKEN);
		i++;
	}
	free_matrix(no_space, -1);
	// print_tokens(minibox);
	minibox->tokens = NULL;
}
