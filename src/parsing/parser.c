/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/09/22 12:02:45 by anshovah         ###   ########.fr       */
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
		input = skip_spaces(input);
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

void	tokenize_input(char *input, t_token *token)
{
	token = get_token(input, token, 0);
}

// parse the input and call the correct functions
// return false if the input is exit
t_bool	parse_input(char *input)
{
	if (ft_strlen(input) == 4 && !ft_strncmp(input, "exit", 4))
	{
		printf("Bye Bye fuckers!\n");
		return (ft_false);
	}
	tokenize_input(input, NULL);
	return (ft_true);
}
