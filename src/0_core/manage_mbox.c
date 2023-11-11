/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:13 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/11 19:34:06 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief	sets all variables in mbox to ini values
 * 
 * 			NOTE: only called once by 'main' on startup
 * 
 * @param mbox 
 * @param env 
 */
void	initialize_box_v2(t_mbox *mbox)
{
	mbox->env = NULL;
	mbox->inp_orig = NULL;
	mbox->inp_trim = NULL;
	mbox->inp_shift = NULL;
	mbox->inp_expand = NULL;
	mbox->error_status = ft_false;
	mbox->history = NULL;
	mbox->tokens = NULL;
	mbox->tmp_token = NULL;
	mbox->root = NULL;
	mbox->tmp_node = NULL;
	initialize_io(mbox);
	mbox->executor.pid = NULL;
	mbox->executor.cmd_av = NULL;
	mbox->count_cycles = 0;
	mbox->print_info = ft_false;
	mbox->consecutive_lt = 0;
	get_mbox(mbox);
}

/**
 * @brief	This is the main freeing function which we call after each cycle
 * 			of treating an input promt.
 * 			It frees all allocated memory and closes all fds related to
 * 			one cycle:
 * 				- free_input_strings_v2
 * 				- free_tokens_v2
 * 				- free_ast_v2
 * 				- close_process_fds_v2
 * 
 * @param	mbox 
 */
void	free_cycle_v2(t_mbox *mbox)
{
	if (!mbox)
		return ;
    free_input_strings_v2(mbox);    
    free_tokens_v2(mbox);
	free_ast_v2(mbox->root);
    mbox->root = NULL;
	close_process_fds_v2(mbox);
	free_process_v2(mbox);
}

/**
 * @brief	check all members of the mbox struct at the end of the program 
 * 			and frees them if they are inizialised.
 * 			then exits with the proper exit status
 * 
 * @param	mbox 
 */
void free_and_close_box_v2(t_mbox *mbox)
{
	int	exit_status;
	
	if (!mbox)
		return ;
	exit_status = ft_atoi(get_var_value(mbox, "?"));
	free_cycle_v2(mbox);
	free_history(mbox);
	free_vars_v2(mbox);
	// dprintf (2, "\n---\nFREE AND CLOSE BOX EXECUTED FOR\n\tPID (%d)\n\tEXIT STATUS (%d)\n---\n", getpid(), exit_status);
    exit(exit_status);
}
