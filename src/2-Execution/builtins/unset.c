/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:25 by astein            #+#    #+#             */
/*   Updated: 2023/10/27 15:13:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    builtin_unset(t_mbox *mbox, t_tree *arg_node)
{
    while (arg_node)
    {
        delete_var(mbox, arg_node->content);
        arg_node = arg_node->right;
    }
}
