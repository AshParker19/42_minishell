/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/10/29 00:50:41 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   - concatenates all the arg nodes values with single space in between
 *          - if flag -n is not present as a FIRST ARG NODE! //TODO:
 *              - adds a '\n'
 *          - writes to the proper FD
 * 
 * @param   mbox 
 * @param   arg_node 
 */
void builtin_echo(t_mbox *mbox, t_ast *arg_node)
{
    bool    print_nl;

    print_nl = true;
    if(arg_node)
    {
        if (str_cmp_strct(arg_node->content, "-n"))
        {
            print_nl = false;
            arg_node = arg_node->right;
        }
        while(arg_node)
        {
            ft_putstr_fd(arg_node->content,
                mbox->executor.io.cmd_fd[CMD_OUT]);
            arg_node = arg_node->right;
            if(arg_node)
                ft_putchar_fd(' ', mbox->executor.io.cmd_fd[CMD_OUT]);
        }
    }
    if (print_nl)
        ft_putchar_fd('\n', mbox->executor.io.cmd_fd[CMD_OUT]);    
}
