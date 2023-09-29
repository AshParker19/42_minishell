/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:05:22 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/29 15:03:11 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int add_offset(int c)
{
	return(c-126);
}

int remove_offset(int c)
{
	return(c+126);
}

bool	ft_isqoute(char c)
{
	return (c == '\'' || c == '"');
}

bool	ft_issep(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v');
}

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
	sp_chars[7] = '{';
	sp_chars[8] = '}';
	sp_chars[9] = 0;
	
	if (!c)
		return (false);
	while (sp_chars[++i])
	{
		if (c == sp_chars[i])
			return (true);
	}
	return (false);
}

/*
   trims all the whitespaces at the beginning and the end 
   of the original string, frees it and returns the trimmed one
*/
// char    *trim_input(char *input)
// {
//     char    *trimmed;

//     trimmed = ft_strtrim(input, " \n\t\v");
//     if (input)
//         free (input);        
//     return (trimmed);
// }


// void	case1(t_minibox *minibox, char *copy, int len)
// {
// 	char	*token;
	
// 	(void)minibox;
// 	while (*copy)
// 	{
// 		len = 0;
// 		if (copy[len] != TRUE_PIPE)
// 		{
// 			while (copy[len] != TRUE)
// 				len++;
// 			printf ("LEN %d\n", len);
// 			break ;	
// 			printf ("TOKEN1 %s\n", ft_substr(copy, 0, len));
// 			copy += len;
// 		}
// 		else if (copy[len] == TRUE_PIPE)
// 		{
// 			token = ft_strchr(copy, TRUE_PIPE);
// 			while (token[len] == TRUE_PIPE)
// 				len++;
// 			printf ("TOKEN2 %s\n", ft_substr(token, 0, len));
// 			copy += len;
// 		}
// 	}
// }

// if (ft_strchr(no_space[i], TRUE_PIPE))
// 		{
// 			len = 0;
// 			if (no_space[i][len] != TRUE_PIPE)
// 			{
// 				while (no_space[i][len] != TRUE_PIPE)
// 					len++;
// 				add_token(minibox, ft_substr(no_space[i], 0, len));		
// 			}
// 			else
// 			{
// 				token = ft_strchr(no_space[i], TRUE_PIPE);
// 				while (token[len] == TRUE_PIPE)
// 				{
// 					token[len] = '|';
// 					len++;
// 				}
// 				add_token(minibox, ft_substr(token, 0, len));		
// 			}
// 		}