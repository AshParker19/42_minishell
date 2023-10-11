/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:46 by astein            #+#    #+#             */
/*   Updated: 2023/10/09 17:24:39 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_env(t_minibox *minibox, char *args)
{
    t_var *cur;

    (void)args; // TODO:
    cur = minibox->vars;
    while(cur)
    {
        ft_putstr_fd(cur->key, 1);
        ft_putchar_fd('=', 1);
        ft_putendl_fd(cur->value, 1);
        cur = cur->next;
    }
}
