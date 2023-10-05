/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:11 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/05 17:55:50 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// t_tree *command_main(t_minibox *minibox)
// {
//     t_tree  *cmd_node;

//     cmd_node = ast_create_node(CMD_NODE);
//     if (!cmd_node)
//         return (NULL);
//     cmd_node = token_list_main(minibox);
//     if(cmd_node)
//         printf("CMD NODE CREATED: %s\n",cmd_node->content);
//     else
//         printf("CMD NODE NOT CREATED\n");
//     return (cmd_node);
// }

// t_tree *command_main(t_minibox *minibox)
// {
//     t_tree  *cmd_node;

//     cmd_node = ast_create_node(CMD_NODE);
//     if (!cmd_node)
//         return (NULL);
//     // minibox->tmp_node = cmd_node;
//     token_list_main(minibox);
//     if (cmd_node && !minibox->tmp_node->content)
//     {
//         delete_ast(minibox->tmp_node);
//         return (NULL);
//     }
//     // minibox->root = minibox->tmp_node; //TODO: move this to job when it's done
//     return cmd_node;
// }

t_tree *command_main(t_minibox *minibox)
{
    // t_tree  *cur_tmp;

    // cur_tmp = ast_create_node(CMD_NODE);
    // if (!cur_tmp)
    //     return(NULL);
    minibox->tmp_node = ast_create_node(CMD_NODE);
    token_list_main(minibox);
    if(minibox->tmp_node && (minibox->tmp_node->content || minibox->tmp_node->left))
    {
        printf("CMD NODE CREATED: %s\n",minibox->tmp_node->content);
        return(minibox->tmp_node);
    }
    else
    {
        printf("CMD NODE NOT CREATED\n");
        return(NULL);
    }
}