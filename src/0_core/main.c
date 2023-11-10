/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/11/10 12:46:05 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal_status;

static void check_args(t_mbox *mbox, int ac, char **av)
{
	if (ac == 1)
		return ;
	if (ac == 2)
	{
		if (av[1] && (str_cmp_strct(av[1], "--info")
			|| str_cmp_strct(av[1], "-i")))
		{
			mbox->print_info = ft_true;
			put_headline("INFO MODE ACTIVATED!", NULL, PURPLE);
			return ;
		}
		else
			put_err_msg("nn", ERR_PROMT, "wrong argument!\nuse: -i ('--info')\n");
	}
	else
		put_err_msg("nn", ERR_PROMT, "wrong number of arguments!");
	set_var_value(mbox, "?", EXIT_STR_FAILURE);
	free_and_close_box_v2(mbox);	
}

/**
 * @brief	
 * 
 * 			SPECIAL INPUTS:
 * 				Just Return		-> readline will read \0	-> exit status 127
 * 				CTRL D			-> readline will read EOF	-> exit minishell (status 0)
 * 
 * @param ac 
 * @param av 
 * @param env 
 * @return int 
 */
int	main(int ac, char **av, char **env)
{
	t_mbox	mbox;
	
	g_signal_status = 0;
	initialize_box_v2(&mbox, env);
	load_vars_v2(&mbox);
	initialize_builtins(&mbox);
	check_args(&mbox, ac, av);
	while (FRANKENSHELL_RISES_AMIDTS_DEATH)
	{
		reset_cycle(&mbox);//TODO:
		mbox.count_cycles++;
		mbox.inp_orig = readline(PROMT);

		char	*exit_status;
	
		if(g_signal_status == SIGNAL_NEW_LINE)
		{
			g_signal_status = 0;
			exit_status = ft_itoa(130);
			set_var_value(&mbox, "?", exit_status);
			free(exit_status);
		}

		if (!mbox.inp_orig)
			builtin_exit(&mbox, NULL); //TODO: really nessesary? YES FOR CRTL + D!
		else if (mbox.inp_orig[0] == '\0')
			set_var_value(&mbox, "?", ft_itoa(127));
		else
		{
			if (*mbox.inp_orig)
				save_history(&mbox, mbox.inp_orig);			
			manage_input(&mbox);
		}
	}
	return (0);
}