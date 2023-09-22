/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/09/22 13:12:08 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	running;

int	main(int argc, char **argv, char** envp)
{
	char	*current_input;

	(void)argc;
	(void)argv;
	(void)envp;
	running = true;

	bultin_echo(argv[1]);

	while (running)
	{
		current_input = readline("MINI-HELL-> ");
		current_input = ft_strtrim(current_input, " \t\f");
		 if (current_input && *current_input)
			add_history(current_input);

		// for CTRL+D
		if(!current_input)
			break;

		// do stuff with the command
		if (parse_input(current_input) == ft_false)
		running = ft_false;
		free(current_input);
	}
		if(!current_input)
			free(current_input);
	return (0);
}
