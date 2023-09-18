/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/09/18 23:08:52 by anshovah         ###   ########.fr       */
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

bool	special_characters(char c, int i)
{	
	char	sp_chars[20];
	
	sp_chars[0] = '|';
	sp_chars[1] = '&';
	sp_chars[2] = '"';
	sp_chars[3] = '\'';
	sp_chars[4] = '>';
	sp_chars[5] = '<';
	sp_chars[6] = '$';
	sp_chars[7] = 0;
	
	if (!c)
		return (false);
	while (sp_chars[++i])
	{
		if (c == sp_chars[i])
			return (true);
	}
	return (false);
}

int	get_flag(char *token, int i)
{
	printf ("HERE\n")	;
	if (special_characters(token[i], -1))
	{
		if (token[i] == '|')
			return (PIPE);
		else if (token[i] == '<' || token[i] == '>')
			return (REDIR);
		else if (token[i] == '$')
			return (DOLLAR_S);
	}
	else if (token[i] == '-' && ft_isalpha(token[i + 1]))
		return (ARG);
	else if (ft_isalpha(token[i]))
		return (CMD);
	return (0);	
}

t_parser *get_token(char *input, t_parser *parser, int i)
{
	int		char_counter;
	char	*token;

	while (input[i])
	{
		char_counter = 0;
		while (ft_isalpha(input[char_counter]))
			char_counter++;
		// printf ("COUNT %d\n", char_counter);	
		if (!ft_isalpha(input[i])) // make it as a command
		{
			token = ft_substr(input, i - char_counter, char_counter);
			printf ("TOKEN %s\n", token);
		}// treat special characters
		i++;		
	}
	return (parser);
	if (!parser)
		return (NULL);
}

void	tokenize_input(char *input, int i, t_parser *parser)
{
	// while (input[++i])
	// {
	// 	if (special_characters(input[i], -1))
	// 	{
	// 		parser = get_token(ft_substr(input), parser);
	// 		printf("SPECIAL\n");
	// 	}
	// 	else
	// 		printf("NOT SPECIAL\n");
	(void)i;
	parser = get_token(input, parser, 0);
	// while (input)
	// {
	// 	// get_token(input, parser);
	// }
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
	tokenize_input(input, -1, NULL);
	return (ft_true);
}
