/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:46 by astein            #+#    #+#             */
/*   Updated: 2023/09/29 18:40:18 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bultin_env(t_minibox *minibox)
{
    t_var *cur;

    cur = minibox->vars;
    while(cur)
    {
        ft_putstr_fd(cur->key, 1);
        ft_putchar_fd('=', 1);
        ft_putendl_fd(cur->value, 1);
        cur = cur->next;
    }
}
