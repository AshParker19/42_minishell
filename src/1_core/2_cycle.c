/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_cycle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2024/01/07 14:41:20 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief	this function frees and NULLs all 5 input strings, if they have
 * 			been allocated before
 * 
 * 			NOTE: function should only be called by 'free_cycle'
 * 
 * @param mbox 
 */
static void	free_inp_strs(t_mbox *mbox)
{
	if(!mbox)
		return ;
	if (mbox->inp_orig)
	{
		free(mbox->inp_orig);
		mbox->inp_orig = NULL;
	}
	if (mbox->inp_trim)
	{
		free(mbox->inp_trim);
		mbox->inp_trim = NULL;
	}
	if (mbox->inp_eq)
	{
		free(mbox->inp_eq);
		mbox->inp_eq = NULL;
	}
	if (mbox->inp_shift)
	{
		free (mbox->inp_shift);
		mbox->inp_shift = NULL;
	}
	if (mbox->inp_expand)
	{
		free(mbox->inp_expand);
		mbox->inp_expand = NULL;
	}
}

/**
 * @brief   This function is kind of the main for an execution cycle!
 *          it follows the sequence below; if any error occurs it reutrns
 * 
 * 			0.	update history
 *          1.  trims all whitespaces from input
 *          2.  marks all seperators ('\', '<', '>', '\'', '"') and whitespaces
 *          3.  expands all the env variables
 *          4.  tokenizes the input string into linked list
 *          5.  parses tokens and builds an AST
 *          6.  executes the AST
 * 
 * @param   mbox 
 */
void	cycle_main(t_mbox *mbox)
{
	if (mbox->inp_orig[0] == '\0')
		return ;
	info_put_banner(mbox, "INPUT STATES", NULL, LIGHT_RED);
	add_history(mbox->inp_orig);
	save_history(mbox);
	info_print_input_str(mbox, "original", mbox->inp_orig, LIGHT_RED);
	mbox->inp_trim = ft_strtrim(mbox->inp_orig, " \n\t\v\a\b\f\r");
	if (!mbox->inp_trim || mbox->inp_trim[0] == 0)
		return ;
	info_print_input_str(mbox, "trimmed", mbox->inp_trim, LIGHT_RED);
	mark_empty_quotes(mbox);
	info_print_input_str(mbox, "empty quotes", mbox->inp_eq, LIGHT_RED);
	if (!shift_seps(mbox, -1, OUT_Q))
		return ;
	info_print_input_str(mbox, "shifted", mbox->inp_shift, LIGHT_RED);
	if (!expand_vars_main(mbox, 0, OUT_Q))
		return ;
	info_print_input_str(mbox, "expanded", mbox->inp_expand, LIGHT_RED);
	if (!tokenize(mbox, 0))
		return ;
	if (!parse(mbox))
		return ;
	if (!mbox->syntax_err_encountered)
		execute_ast(mbox);
}

/**
 * @brief	This is the main freeing function which we call after each cycle
 * 			of treating an input promt.
 * 			It frees all allocated memory and closes all fds related to
 * 			one cycle:
 * 				- free_inp_strs
 * 				- free_tokens
 * 				- free_ast
 * 				- close_fds
 * @brief   this function frees and resets everthting thats needed to process
 *          one cycle
 * 
 * 
 * @param	mbox 
 */
void	reset_cycle(t_mbox *mbox)
{
	if (!mbox)
		return ;
	free_inp_strs(mbox);
	free_tokens(mbox);
	free_ast(mbox->ast);
	mbox->ast = NULL;
	close_fds(mbox);
	free_process(mbox);
	mbox->exec.io.prev_pipe[P_LEFT] = -1;
	mbox->exec.io.prev_pipe[P_RIGHT] = -1;
	mbox->exec.pid_index = 0;
	conf_sig_handler(SIG_STATE_MAIN);
	g_signal_status = 0;
	mbox->consecutive_lt = 0;
	mbox->syntax_err_encountered = ft_false;
}
