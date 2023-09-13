/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/09/13 17:00:10 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).

• Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.

• Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).

*/

// parse the input and call the correct functions
// return false if the input is exit
t_bool	parse_input(char *input)
{
	if (ft_strlen(input) == 4 && !ft_strncmp(input, "exit", 4))
	{
		printf("Bye Bye fuckers!\n");
		return (ft_false);
	}
	return (ft_true);
}
