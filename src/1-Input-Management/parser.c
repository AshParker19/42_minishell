/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/09/29 13:05:02 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	TODO: Make a abstract syntax tree tokens stored in the linked list
    minibox->tokens
	
    the result will be stored in the root of minibox
    minibox->root
    
*/
void	parse(t_minibox *minibox)
{
    (void)minibox;
    //TODO:
}

// void	print_type(t_token *head)
// {
// 	t_token *current = head;
// 	while (current)
// 	{
// 		printf (GREEN"----------\n"RESET);
// 		printf ("token ---> %s\n type ---> ", current->token_value);
// 		if (current->type == WORD)
// 			printf ("Word");
// 		else if (current->type == PIPE)
// 			printf ("Pipe");
// 		else if (current->type == DOLLAR)
// 			printf ("Dollar Sign");
// 		else if (current->type == DB_QUOTE)
// 			printf ("Double Quotes");
// 		else if (current->type == SN_QUOTE)
// 			printf ("Single Quotes");
// 		else if (current->type == REDIREC)	
// 			printf ("Redirection");
// 		printf ("\n");
// 		printf (GREEN"----------\n"RESET);
// 		current = current->next;
// 	}
// }

// int	get_flag(char c)
// {
// 	if (c == '|')
// 		return (PIPE);
// 	else if (c == '<' || c == '>')
// 		return (REDIREC);
// 	else if (c == '$')
// 		return (DOLLAR);
// 	else if (c == '\'')
// 		return (SN_QUOTE);
// 	else if (c == '"')
// 		return (DB_QUOTE);	
// 	return (0);	
// }

