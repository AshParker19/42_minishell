/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/10/11 17:59:15 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minibox	minibox;
	(void)ac;
	(void)av;
	initialize_box(&minibox, env);
	load_vars(&minibox);
	load_executor(&minibox);
	test_builtins(&minibox);
	
	while (1)
	{
		minibox.input_original = readline("MINI-HELL-> ");
		if (!minibox.input_original)
			return (0);
		// do stuff with the command
		manage_input(&minibox);
	}
	return (0);
}