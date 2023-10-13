/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:46 by astein            #+#    #+#             */
/*   Updated: 2023/10/14 00:05:35 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_env(t_minibox *minibox, t_tree *arg_node)
{
    (void)minibox;
    (void)arg_node;
    char    *error_msg;
    t_var   *cur;
    
    if(arg_node)
    {
        error_msg = ft_strcat_multi(3, "env: ‘", arg_node->content, "’: No such file or directory");
        ft_putendl_fd(error_msg, 1);
        free(error_msg);
    }
    else
    {
        cur = minibox->vars;
        while(cur)
        {
            ft_putstr_fd(cur->key, 1);
            ft_putchar_fd('=', 1);
            ft_putendl_fd(cur->value, 1);
            cur = cur->next;
        }
    }
}
