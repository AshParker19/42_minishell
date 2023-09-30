/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:14 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/30 17:10:36 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).

• Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.

• Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
*/

void	print_tokens(t_minibox *minibox)
{
    t_token   *current;
	
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
static void    add_token(t_minibox *minibox, char *value)
{
    t_token   *new_t;
    t_token   *current;
    
    new_t = ft_calloc(1, sizeof(t_token));
    if (!new_t)
	{
        return ;
	}
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
	receives the substing with a special character between words,
	splits them into words and characters and adds new tokens to minibox->tokens
*/
static void	split_by_sep(t_minibox *minibox, char *copy, int len)
{
	int	quote_state;
	
	quote_state = OUT_Q;
	while (*copy)
	{
        update_qoute_state(&quote_state, *copy);
		if (quote_state == OUT_Q)
		{
			if (ft_issep(remove_offset(*copy)))
			{
				add_token(minibox, ft_substr(copy, 0, 1));
				copy++;
			}
			else
			{
				len = 0;
				while (copy[len])
				{
					if (ft_issep(remove_offset(copy[len]))
						|| ft_isqoute(remove_offset(copy[len]))) 
						break ; 
					len++;
				}
				add_token(minibox, ft_substr(copy, 0, len));
				copy += len;
			}	
		}
		else
		{
			len = 0;
			while (copy[len])
			{
				if (quote_state == OUT_Q)
					break ; 	
				update_qoute_state(&quote_state, copy[len]);
				len++;
			}
			if (quote_state != OUT_Q)
				add_token(minibox, ft_substr(copy, 0, len));
			copy += len;

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
			split_by_sep(minibox, no_space[i], 0);		
		}
		else
			add_token(minibox, ft_strdup(no_space[i]));
		i++;
	}
	free_matrix(no_space, -1);
	print_tokens(minibox);
	minibox->tokens = NULL;
}
