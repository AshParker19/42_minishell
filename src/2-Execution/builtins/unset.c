/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:25 by astein            #+#    #+#             */
/*   Updated: 2023/10/13 23:00:40 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// TODO: FREE NOT PROBERLY DONE!
void    builtin_unset(t_minibox *minibox, t_tree *arg_node)
{
    (void)minibox;
    (void)arg_node;
    // t_var *temp;
    // t_var *temp_last;

    // temp = minibox->vars;
    // temp_last = temp;

    // while(temp)
    // {
    //     if(ft_strcmp_strict(key, temp->key))
    //     // if(ft_strlen(key) == ft_strlen(temp->key))
    //     // {
    //     //     if(!ft_strncmp(key, temp->key, ft_strlen(key)))
    //         {
    //             if(temp_last == temp)
    //             {
    //                 // first node delete
    //                 minibox->vars = temp->next;
    //             }
    //             else
    //                 temp_last->next = temp->next;
    //             free(temp);
    //             break;
    //         }
    //     // }
    //     temp_last = temp;
    //     temp = temp->next;
    // }
}