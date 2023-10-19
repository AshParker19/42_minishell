/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/10/19 19:52:24 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_echo(t_minibox *minibox, t_tree *arg_node)
{
    bool    print_nl;

    print_nl = true;
    if(arg_node)
    {
        if (ft_strcmp_strict(arg_node->content, "-n"))
        {
            print_nl = false;
            arg_node = arg_node->right;
        }
        while(arg_node)
        {
            ft_putstr_fd(arg_node->content, minibox->executor.io.cmd_fd[CMD_OUT]);
            arg_node = arg_node->right;
            if(arg_node)
                ft_putchar_fd(' ', minibox->executor.io.cmd_fd[CMD_OUT]);
        }
    }
    if (print_nl)
        ft_putchar_fd('\n', minibox->executor.io.cmd_fd[CMD_OUT]);    
}
