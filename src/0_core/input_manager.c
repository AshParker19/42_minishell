/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/11 01:52:47 by astein           ###   ########.fr       */
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
void	manage_input(t_mbox *mbox) //TODO: rename function and file into input main
{
    mbox->error_status = ft_false; //TODO: understand this shit again
    add_history(mbox->inp_orig);
    display_info_str(mbox, "input original", mbox->inp_orig);
    mbox->inp_trim = ft_strtrim(mbox->inp_orig, " \n\t\v\a\b\f\r");
    if (!mbox->inp_trim || mbox->inp_trim[0] == 0)
        return ;
    display_info_str(mbox, "input trimmed", mbox->inp_trim);
    if (!shift_context_chars(mbox, 0, 0))
        return ;
    display_info_str(mbox, "input shifted", mbox->inp_shift);
    if (!expand_variables(mbox, 0, OUT_Q))
        return ;
    display_info_str(mbox, "input expanded", mbox->inp_expand);

    if (!tokenize(mbox, 0))
        return ;

    print_parser_output(mbox, ft_true);
    if (!parse(mbox))
        return ;
    print_parser_output(mbox, ft_false);
            
    if (mbox->root->type == CMD_NODE && str_cmp_strct(mbox->root->content, "exit"))
	{
        builtin_exit(mbox, mbox->root->right);
		return ;
	}
        
    if (mbox->error_status == ft_false)
    {
        print_executor_output(mbox, ft_true);
        execute(mbox); //TODO: why don't we check if it fails
        print_executor_output(mbox, ft_false); 
    }
}
