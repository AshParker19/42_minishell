/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/04 18:39:11 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   this function is kind of the main for an execution cycle!
 *          it follows the sequence below; if any error occurs it reutrns
 * 
 *          1.  trims all whitespaces from input
 *          2.  marks all seperators ('\', '<', '>', '\'', '"') and whitespaces
 *          3.  expands all the env variables
 *          4.  tokenizes the input string into linked list
 *          5.  parses tokens and builds an AST
 *          6.  executes the AST
 * 
 * @param   mbox 
 */
void	input_main(t_mbox *mbox)
{
	if (mbox->inp_orig[0] == '\0')
		return ;
	add_history(mbox->inp_orig); //TODO: CHECK on School
	mbox->error_status = ft_false; //TODO: understand this shit again
	display_info_str(mbox, "input original", mbox->inp_orig);
	mbox->inp_trim = ft_strtrim(mbox->inp_orig, " \n\t\v\a\b\f\r");
	if (!mbox->inp_trim || mbox->inp_trim[0] == 0)
		return ;
	display_info_str(mbox, "input trimmed", mbox->inp_trim);
	save_history(mbox);	
	if (!shift_context_chars(mbox, -1, OUT_Q))
		return ;
	display_info_str(mbox, "input shifted", mbox->inp_shift);
	if (!expand_vars_main(mbox, 0, OUT_Q))
		return ;
	display_info_str(mbox, "input expanded", mbox->inp_expand);
	if (!tokenize(mbox, 0))
		return ;
	if (!parse(mbox))
		return ;
	if (mbox->error_status == ft_false)
		execute(mbox);
}
