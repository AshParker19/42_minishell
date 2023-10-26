/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/10/26 19:53:25 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minibox	minibox;
	(void)ac;
	(void)av;
	initialize_box(&minibox, env);
	// initialize_signals();
	load_vars(&minibox);
	load_executor(&minibox);
	// test_builtins(&minibox);
	
	while (1)
	{
		minibox.inp_orig = readline(PROMT);
		if (!minibox.inp_orig)
			builtin_exit(&minibox, NULL);
		else
			// do stuff with the command
			manage_input(&minibox);
	}
	return (0);	
}