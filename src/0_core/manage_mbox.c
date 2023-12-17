/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:13 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/17 16:59:06 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief   All frankenshell aka minishell related variables are stored in the
 * 			mbox struct. This file contains all functions related to the
 * 			initialization, freeing, and closing of the mbox struct.
 * 			It contains the following functions:
 * 				- initialize_mbox
 * 				- destroy_mbox
 * 				- destroy_mbox_with_exit
 */

#include "frankenshell.h"

/**
 * @brief   Initializes the mbox struct with the default values.
 *			
 			NOTE: only called once by 'main' on startup 
			
 * @param   mbox        
 * @param   env         
 */
void	initialize_mbox(t_mbox *mbox, char **env)
{
	g_signal_status = 0;
	mbox->info_mode = ft_false;
	mbox->error_status = ft_false;
	mbox->count_cycles = 0;
	mbox->history_lst = NULL;
	mbox->env = NULL;
	mbox->inp_orig = NULL;
	mbox->inp_trim = NULL;
	mbox->inp_shift = NULL;
	mbox->inp_expand = NULL;
	mbox->consecutive_lt = 0;
	mbox->tokens = NULL;
	mbox->tmp_token = NULL;
	mbox->ast = NULL;
	mbox->tmp_node = NULL;
	mbox->exec.pid = NULL;
	initialize_io(mbox, NULL, 0);
	initialize_vars(mbox, env);
	initialize_builtins(mbox);
}

/**
 * @brief   Whenever a frankenshell process is created, before terminating it,
 * 			we have to free all the allocated memory and close all the open fds.
 * 			After cleaning up, we exit with the proper exit status.
 *			
 * @param   mbox        
 */
void	destroy_mbox(t_mbox *mbox)
{
	int	exit_status;

	if (!mbox)
		return ;
	exit_status = ft_atoi(get_var_value(mbox, "?"));
	reset_cycle(mbox);
	ft_lstclear(&(mbox->history_lst), del_history_node);
	free_vars_v2(mbox);
	exit(exit_status);
}

t_bool	destroy_mbox_with_exit(t_mbox *mbox, int exit_status)
{
	set_var_value_int(mbox, "?", exit_status);
	destroy_mbox(mbox);
	return (ft_false);
}
