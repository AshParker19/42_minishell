/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/11/06 14:31:08 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_mbox	mbox;
	
	(void)ac;
	(void)av; //TODO: print shit with arg --info
	initialize_box_v2(&mbox, env);
	load_vars_v2(&mbox);
	initialize_builtins(&mbox);
	// free_cycle_v2(&mbox); //TODO: move it somewhere better place
	// test_builtins(&mbox);
	
	while (1)
	{
		reset_cycle(&mbox);//TODO:
		mbox.count_cycles++;
		mbox.inp_orig = readline(PROMT);
		if (!mbox.inp_orig)
			builtin_exit(&mbox, NULL); //TODO: really nessesary? YES FOR CRTL + D!
		else
		{
			if (*mbox.inp_orig)
				save_history(&mbox, mbox.inp_orig);			
			manage_input(&mbox);
		}
	}
	return (0);	
}