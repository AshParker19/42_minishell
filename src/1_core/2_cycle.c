/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_cycle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/19 02:01:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

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
	info_print_input_string(mbox, "original", mbox->inp_orig, LIGHT_RED);
	mbox->inp_trim = ft_strtrim(mbox->inp_orig, " \n\t\v\a\b\f\r");
	if (!mbox->inp_trim || mbox->inp_trim[0] == 0)
		return ;
	info_print_input_string(mbox, "trimmed", mbox->inp_trim, LIGHT_RED);
	mark_empty_quotes(mbox);
	info_print_input_string(mbox, "empty quotes", mbox->inp_eq, LIGHT_RED);
	if (!shift_seps(mbox, -1, OUT_Q))
		return ;
	info_print_input_string(mbox, "shifted", mbox->inp_shift, LIGHT_RED);
	if (!expand_vars_main(mbox, 0, OUT_Q))
		return ;
	info_print_input_string(mbox, "expanded", mbox->inp_expand, LIGHT_RED);
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
 * 				- free_input_strings_v2
 * 				- free_tokens_v2
 * 				- free_ast_v2
 * 				- close_process_fds_v2
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
	free_input_strings_v2(mbox);
	free_tokens_v2(mbox);
	free_ast_v2(mbox->ast);
	mbox->ast = NULL;
	close_process_fds_v2(mbox);
	free_process_v2(mbox);
	mbox->exec.io.prev_pipe[P_LEFT] = -1;
	mbox->exec.io.prev_pipe[P_RIGHT] = -1;
	mbox->exec.pid_index = 0;
	conf_sig_handler(SIG_STATE_MAIN);
	g_signal_status = 0;
	mbox->consecutive_lt = 0;
	mbox->syntax_err_encountered = ft_false;
}
