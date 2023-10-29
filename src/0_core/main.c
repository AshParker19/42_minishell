/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/10/29 01:02:09 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mbox	mbox;
	(void)ac;
	(void)av; //TODO: print shit with arg --info
	initialize_box_v2(&mbox, env);
	// initialize_signals();
	load_vars_v2(&mbox);
	initialize_builtins(&mbox);
	// free_cycle_v2(&mbox); //TODO: move it somewhere better place
	// test_builtins(&mbox);
	
	while (1)
	{
		reset_cycle(&mbox);//TODO:
		mbox.inp_orig = readline(PROMT);
		if (!mbox.inp_orig)
			builtin_exit(&mbox, NULL); //TODO: really nessesary?
		else
			// do stuff with the command
			manage_input(&mbox);
	}
	return (0);	
}