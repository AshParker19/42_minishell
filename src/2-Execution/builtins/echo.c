/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/10/13 23:13:01 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_echo(t_minibox *minibox, t_tree *arg_node)
{
    (void)minibox;
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
            ft_putstr_fd(arg_node->content, 1);
            arg_node = arg_node->right;
            if(arg_node)
                ft_putchar_fd(' ', 1);
        }
    }
    if (print_nl)
        ft_putchar_fd('\n', 1);    
}
