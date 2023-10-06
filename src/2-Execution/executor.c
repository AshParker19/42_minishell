/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/06 19:25:46 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute(t_minibox *minibox)
{
    // Easy test case for only 1 cmd (no pipes no redirs) && only builtins
    int builtin_cmd_index;
    
    if(minibox->root->type == CMD_NODE)
    {
        builtin_cmd_index = check_if_builtin(minibox, minibox->root->content);
        if(builtin_cmd_index != -1)
        {
            run_builtin(minibox->root, builtin_cmd_index);
        }
        else
                ; // execute from path -> cmd name could be wrong / invalid
    }
}

void execute_command()
{
    
}