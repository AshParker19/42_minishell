/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:06:17 by astein            #+#    #+#             */
/*   Updated: 2023/12/14 18:13:53 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status;

static void	check_args(t_mbox *mbox, int ac, char **av)
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
			err_msg(mbox, EXIT_FAILURE, "nn", ERR_P, WA_F);
	}
	else
		err_msg(mbox, 1, "nn", ERR_P, WN);
	set_var_value_int(mbox, "?", EXIT_FAILURE);
	free_and_close_box_v2(mbox);
}

/**
 * @brief	Here we go! The main function of the frankenshell.
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

/**
 * @brief    Here we go! The main function of the frankenshell.
 * 			
 * 			 For more details, see [documentation.md](../docs/documentation.md)
 * 				link:../docs/documentation.md
 * * 				link:"../docs/documentation.md"
 * 
 * @param    ac        
 * @param    av        
 * @param    env       
 * @return   int       
 */
int	main(int ac, char **av, char **env)
{
	t_mbox	mbox;

	initialize_box_v2(&mbox, env);
	check_args(&mbox, ac, av);
	increment_shlvl(&mbox);
	while (FRANKENSHELL_RISES_AMIDTS_DEATH)
	{
		reset_cycle(&mbox);
		mbox.count_cycles++;
		mbox.inp_orig = readline(PROMPT);
		if (g_signal_status == SIGNAL_NEW_LINE)
		{
			g_signal_status = 0;
			set_var_value_int(&mbox, "?", 130);
		}
		if (!mbox.inp_orig)
			builtin_exit(&mbox, NULL);
		else
			input_main(&mbox);
	}
}
