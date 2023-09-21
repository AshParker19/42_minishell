/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/09/21 21:57:17 by anshovah         ###   ########.fr       */
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
			printf ("Double Quote");
		else if (current->type == SN_QUOTE)
			printf ("Single Quote");
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


t_token *get_token(char *input, t_token *token, int len)
{
	// t_bool flg_dbl_qoute;
	
	while (*input)
	{
		input = skip_spaces(input);
		if (ft_isalpha(*input))
		{
			token = ft_addback(token, cut_word(input, 0, &len, 0), WORD);
			input += len;
		}
		else if (*input == '-' && *input + 1)
		{
			token = ft_addback(token, cut_word(input, 1, &len, 0), WORD);
			input += len;
		}
		else if (special_characters(*input, -1))
		{
			if (*input == '\'' || *input == '"')
			{
				// while(*input != '"')
				// 	input++;		
				token = ft_addback(token, cut_word(input, 0, &len, 1), //length for quotes here
					get_flag(*input));
				input += len;				
			}
			else
				token = ft_addback(token, cut_word(input, 0, &len, 1),
					get_flag(*input));
			input++;
		}
		// else
		// 	input++;
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
