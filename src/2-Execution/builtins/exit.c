/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:57 by astein            #+#    #+#             */
/*   Updated: 2023/10/27 15:13:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: return the last child exit satus
// TODO: check signal
// TODO: CHANGE env SHLVL to -=1
void    builtin_exit(t_mbox *mbox, t_tree *arg_node)
{
    printf("exit\n");
    if (arg_node && !ft_str_is_numeric(arg_node->content))
        create_error_msg("nnnn", ERR_PROMT, "exit: ", arg_node->content,  
            ": numeric argument required");
    // TODO: decrease SHLEVL
    // TODO: NOT SURE IF I CAN DO IT HERE, BECAUSE THE ENV NEEDS TO CHANGE IN THE PARENT NOT IN THE CHILD!
    // TODO: Deal with exit status!

    free_and_close_box(mbox, -100);
    exit(0);
    

    // SHLVL
    // 1
    // ./minishell         SHLVL
    // 2                   2
    //                     ./minishell         SHLVL
    //                     3                   3
    //                                         exit
    //                     3
    //                     2
    //                     exit
    // 2
    // 1
}
