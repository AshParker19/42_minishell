/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/27 15:13:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser_output(t_mbox *mbox);

// dealing with everything thats before exection
void	manage_input(t_mbox *mbox)
{
    mbox->error_status = false;
    add_history(mbox->inp_orig);
    printf("mbox->input_original:\t(%s)\n", mbox->inp_orig);
    mbox->inp_trim = ft_strtrim(mbox->inp_orig, " \n\t\v");
    printf("mbox->inp_trim:\t\t(%s)\n", mbox->inp_trim);
    mark_seps(mbox, 0, 0);
    printf("mbox->inp_shift:\t\t(%s)\n", mbox->inp_shift);
    expand_variables(mbox, 0, 0, OUT_Q);
    printf("mbox->inp_expand:\t(%s)\n", mbox->inp_expand);
    if (*mbox->inp_expand == '\0')
    {
            free_cycle(mbox);
            return ;
    }
    tokenize(mbox, 0); // TODO: we dont check if it returns error
    parse(mbox);
    if (mbox->root->type == CMD_NODE && ft_strcmp_strict(mbox->root->content, "exit"))
        builtin_exit(mbox, mbox->root->right);
    print_parser_output(mbox);
    if (mbox->error_status == false)
    {
        print_executor_output(mbox, 0);
        execute(mbox);
        print_executor_output(mbox, 1); 
    }
    free_cycle(mbox);
}
