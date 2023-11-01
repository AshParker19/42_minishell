/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/31 21:48:11 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser_output(t_mbox *mbox);


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
void	manage_input(t_mbox *mbox)
{
    mbox->error_status = ft_false; //TODO: understand this shit again
    add_history(mbox->inp_orig);
    printf("mbox->input_original:\t(%s)\n", mbox->inp_orig);
    mbox->inp_trim = ft_strtrim(mbox->inp_orig, " \n\t\v\a\b\f\r");
    if (!mbox->inp_trim || mbox->inp_trim[0] == 0)
        return ;
    printf("mbox->inp_trim:\t\t(%s)\n", mbox->inp_trim);

    if (!mark_seps(mbox, 0, 0))
        return ;
    printf("mbox->inp_shift:\t(%s)\n", mbox->inp_shift);

    if (!expand_variables(mbox, 0, 0, OUT_Q))
        return ;
    printf("mbox->inp_expand:\t(%s)\n", mbox->inp_expand);

    if (!tokenize(mbox, 0))
        return ;

    if (!parse(mbox))
        return ;
            
    if (mbox->root->type == CMD_NODE && str_cmp_strct(mbox->root->content, "exit"))
        builtin_exit(mbox, mbox->root->right);
        
    print_parser_output(mbox);
    if (mbox->error_status == ft_false)
    {
        print_executor_output(mbox, 0);
        execute(mbox);
        print_executor_output(mbox, 1); 
    }
}
