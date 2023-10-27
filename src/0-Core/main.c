/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/10/27 15:13:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mbox	mbox;
	(void)ac;
	(void)av;
	initialize_box(&mbox, env);
	// initialize_signals();
	load_vars(&mbox);
	load_executor(&mbox);
	// test_builtins(&mbox);
	
	while (1)
	{
		mbox.inp_orig = readline(PROMT);
		if (!mbox.inp_orig)
			builtin_exit(&mbox, NULL);
		else
			// do stuff with the command
			manage_input(&mbox);
	}
	return (0);	
}