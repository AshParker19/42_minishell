/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/09/24 17:08:02 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	running;

void	initialize_box(t_minibox *minibox, char **env)
{
	minibox->env = env;
	minibox->input = NULL;
	minibox->tokens = NULL;
	minibox->vars = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_minibox	minibox;
	
	(void)ac;
	(void)av;
	running = true;
	initialize_box(&minibox, env);
	while (running)
	{
		minibox.input = readline("MINI-HELL-> ");
		if (!minibox.input)
			return (0);
		add_history(minibox.input);
		// do stuff with the command
		if (parse_input(&minibox) == ft_false)
			running = ft_false;
		// free(current_input);
	}
	return (0);
}