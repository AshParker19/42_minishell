/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cycle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/17 19:21:35 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   this function is kind of the main for an execution cycle!
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
	mbox->error_status = ft_false;
	info_print_input_string(mbox, "input original", mbox->inp_orig, LIGHT_RED);
	mbox->inp_trim = ft_strtrim(mbox->inp_orig, " \n\t\v\a\b\f\r");
	if (!mbox->inp_trim || mbox->inp_trim[0] == 0)
		return ;
	info_print_input_string(mbox, "input trimmed", mbox->inp_trim, LIGHT_RED);
	if (!shift_context_chars(mbox, -1, OUT_Q))
		return ;
	info_print_input_string(mbox, "input shifted", mbox->inp_shift, LIGHT_RED);
	if (!expand_vars_main(mbox, 0, OUT_Q))
		return ;
	info_print_input_string(mbox, "input expanded", mbox->inp_expand, LIGHT_RED);
	if (!tokenize(mbox, 0))
		return ;
	if (!parse(mbox))
		return ;
	if (mbox->error_status == ft_false)
		execute_ast(mbox);
}
