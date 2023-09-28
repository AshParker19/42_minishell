/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:14 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/28 12:22:28 by anshovah         ###   ########.fr       */
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

int	get_flag(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<' || c == '>')
		return (REDIREC);
	else if (c == '$')
		return (DOLLAR);
	else if (c == '\'')
		return (SN_QUOTE);
	else if (c == '"')
		return (DB_QUOTE);	
	return (0);	
}

void	print_type(t_token *head)
{
	t_token *current = head;
	while (current)
	{
		printf (GREEN"----------\n"RESET);
		printf ("token ---> %s\n type ---> ", current->token_value);
		if (current->type == WORD)
			printf ("Word");
		else if (current->type == PIPE)
			printf ("Pipe");
		else if (current->type == DOLLAR)
			printf ("Dollar Sign");
		else if (current->type == DB_QUOTE)
			printf ("Double Quotes");
		else if (current->type == SN_QUOTE)
			printf ("Single Quotes");
		else if (current->type == REDIREC)	
			printf ("Redirection");
		printf ("\n");
		printf (GREEN"----------\n"RESET);
		current = current->next;
	}
}

char	*cut_word(char *str, int i, int *len, int option)
{
	char	*skip;
	
	// if (!str)
	// 	return (NULL);
	while (ft_isalpha(str[i]))
		i++;
	*len = i;	
	skip = ft_substr(str, 0, i + option);
	return (skip);
}

int	quote_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		i++;	
	while (str[i] != '"' && str[i] != '\'')
		i++;
	return (i + 1);	
}

t_token *get_token(char *input, t_token *token, int len)
{
	while (*input)
	{
		if (ft_isalpha(*input))
		{
			token = ft_addback(token, cut_word(input, 0, &len, 0), WORD);
			input += len;
		}
		else if ((*input == '-' && *input + 1)
			|| (*input == '-' && *input + 1 == '-' && *input + 2))
		{
			token = ft_addback(token, cut_word(input, 2, &len, 0), WORD); // 0 here to not to put a special character after a word
			input += len;
		}
		else if (special_characters(*input, -1))
		{
			if (*input == '\'' || *input == '"') // check if quotes are closed
			{
				len = quote_len(input);
				token = ft_addback(token, ft_substr(input, 0, len), //length for quotes here
					get_flag(*input));
				input += len;				
			}
			else
			{
					token = ft_addback(token, cut_word(input, 0, &len, 1),
						get_flag(*input));
				input++;
			}
		}
		else
			input++;
	}
	print_type(token);
	return (token);
}

/*
	TODO: Make a linked list with the tokens grabbed from 
	minibox->input_expaned

    the result will be stored in the linked list:
    minibox->tokens
*/
void	tokenize(t_minibox *minibox, int i)
{
	// int	j = 0;
	// int	len = 0;
	// char sep = -1;
	// char	cur_c;
	(void)minibox;
	i++;
	// char	**no_pipes;
	// char	*token = NULL;

	// token++;
	// no_pipes = ft_split(minibox->input_expanded, TP);
	// // while (no_pipes[i])
	// // {
	// // 	if (no_pipes[i][j])
	// // 		//...
	// // }
	// i = 0;
	// while (no_pipes[i])
	// {
	// 	printf ("╟%s╢\n", no_pipes[i]);
	// 	i++;
	// }
	// printf ("NO PIPE ╟%s╢\n", minibox->input_expanded);
}


// void	tokenize(t_minibox *minibox, int i)
// {
// 	int		len;
// 	int		start;
// 	char	*token = NULL;
// 	char	cur_c;
	
// 	printf("TOKENIZER STARTED....\n");
// 	while (minibox->input_expanded[i])
// 	{
// 		len = 0;
// 		// to treat the argument which is in quotes and consists of more than one word
// 		if (minibox->input_expanded[i] == '\'' || minibox->input_expanded[i] == '"')
// 		{
// 			cur_c = minibox->input_expanded[i];
// 			start = i;
// 			while (minibox->input_expanded[i] == cur_c) // if there's more than one quote one after another
// 			{
// 				len++;
// 				i++; // skip quote
// 			}
// 			while (minibox->input_expanded[i])
// 			{
				
// 				if (minibox->input_expanded[i] == cur_c)
// 				{
// 					while (minibox->input_expanded[i] == cur_c) // if  more quotes after. fucked up cases like:"''world''''"   "'''world'''''" 
// 					{
// 						len++;
// 						i++;
// 					}
// 					token = ft_substr(minibox->input_expanded, start, len);
// 					printf ("╟%s╢", token);
// 					break ;
// 				}
// 				len++;
// 				i++;
// 			}
// 		}
		
// 		// else if (!ft_isspace(minibox->input_expanded[i]))
// 		// {
// 		// 	start = i;
// 		// 	while (minibox->input_expanded[i]) 
// 		// 	{
// 		// 		if (minibox->input_expanded[i] == '|') // look for a pipe between 2 arguments with no spaces
// 		// 		{
// 		// 			printf ("TATATATA\n");
// 		// 			token = ft_strchr(minibox->input_expanded, '|');
// 		// 			token = ft_substr(minibox->input_expanded, start, 
// 		// 				ft_strlen(minibox->input_expanded) - ft_strlen(token));
// 		// 			i += ft_strlen(token);	
// 		// 			printf ("╟%s╢", token);
// 		// 		}
// 		// 		else if (ft_isspace(minibox->input_expanded[i]))
// 		// 		{
// 		// 			token = ft_strchr(minibox->input_expanded, minibox->input_expanded[i]);
// 		// 			printf ("***%s***\n", token);
// 		// 			token = ft_substr(minibox->input_expanded, start, 
// 		// 				ft_strlen(minibox->input_expanded) - ft_strlen(token));
// 		// 			i += ft_strlen(token);	
// 		// 			printf ("╟%s╢", token);
// 		// 		}
// 		// 		else
// 		// 			i++;
// 		// 	}
// 		// }
// 		else
// 			i++;
// 	}
// 	printf ("\n");
// }

