/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:14 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/29 13:04:51 by anshovah         ###   ########.fr       */
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
    if(!new_t)
        return;
    new_t->value = value;
    if(!minibox->tokens)
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
	splits them into words and characters and adds new tokens to minibox
*/
static void	split_by_sep(t_minibox *minibox, char *copy, int len)
{
	while (*copy)
	{
		if (*copy != TRUE_PIPE)
		{
			len = 0;
			while (copy[len])
			{
				if (copy[len] == TRUE_PIPE)
					break ; 
				len++;
			}
			add_token(minibox, ft_substr(copy, 0, len));
			copy += len;
		}
		else if (*copy == TRUE_PIPE)
		{
			add_token(minibox, ft_substr(copy, 0, 1));
			copy++;
		}
	}
}

/*
	TODO: Make a linked list with the tokens grabbed from 
	minibox->input_expaned

    the result will be stored in the linked list:
    minibox->tokens
*/
void	tokenize(t_minibox *minibox, int i)
{
	char	**no_space;

	no_space = ft_split(minibox->input_expanded, NO_SPACE); //\n\v\t
	while (no_space[i])
	{
		if (ft_strchr(no_space[i], TRUE_PIPE))
			split_by_sep(minibox, no_space[i], 0);
		else
			add_token(minibox, ft_strdup(no_space[i]));
		i++;
	}
	free_matrix(no_space, -1);
	print_tokens(minibox);
	minibox->tokens = NULL;
}
