/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/11/08 16:04:06 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void check_args(t_mbox *mbox, int ac, char **av)
{
	if (ac == 1)
		return ;
	if (ac == 2)
	{
		if (av[1] && str_cmp_strct(av[1], "--info"))
		{
			mbox->print_info = ft_true;
			printf(PURPLE"----\nADDITIONAL INFO WILL BE PRINTED!\n----\n"RESET);
			return ;
		}
		else
			put_err_msg("nn", ERR_PROMT, "wrong argument!\nuse: '--info'\n");
	}
	else
		put_err_msg("nn", ERR_PROMT, "wrong number of arguments!");
	set_var_value(mbox, "?", ft_itoa(EXIT_FAILURE));
	free_and_close_box_v2(mbox);	
}

int	main(int ac, char **av, char **env)
{
	t_mbox	mbox;
	
	initialize_box_v2(&mbox, env);
	load_vars_v2(&mbox);
	initialize_builtins(&mbox);
	check_args(&mbox, ac, av);
	
	while (FRANKENSHELL_RISES_AMIDTS_DEATH)
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