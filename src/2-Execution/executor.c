/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/07 16:44:41 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pipe_case()

void    execute(t_minibox *minibox)
{
    int builtin_cmd_index;
    initialize_executor(minibox);
    
    if(minibox->root->type == CMD_NODE)
    {
        builtin_cmd_index = check_if_builtin(minibox, minibox->root->content);
        if(builtin_cmd_index != -1)
            run_builtin(minibox->root, builtin_cmd_index);
        else
        {
            single_cmd(minibox, minibox->root,
                find_cmd(minibox, minibox->root->content, -1));
            wait(NULL);                 
        }
    }
    else
        pipe_case(minibox);
}
