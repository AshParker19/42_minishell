/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:57 by astein            #+#    #+#             */
/*   Updated: 2023/10/13 23:00:24 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_exit(t_minibox *minibox, t_tree *arg_node)
{
    (void)minibox;
    (void)arg_node; //TODO:

    // TODO: CHANGE env SHLVL to -=1

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
    
    // NOT SURE IF I CAN DO IT HERE, BECAUSE THE ENV NEEDS TO CHANGE IN THE PARENT NOT IN THE CHILD!
    free_and_close_box(minibox, -100);
}




