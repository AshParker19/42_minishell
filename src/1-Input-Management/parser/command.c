/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:11 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/04 13:24:06 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_tree *command_main(t_minibox *minibox)
{
    t_tree  *cmd_node;

    cmd_node = ast_create_node(CMD_NODE);
    if (!cmd_node)
        return (NULL);
    minibox->tmp_node = cmd_node;
    token_list_main(minibox);
    if (cmd_node && !minibox->tmp_node->content)
    {
        delete_ast(minibox->tmp_node);
        return (NULL);
    }
    minibox->root = minibox->tmp_node; //TODO: move this to job when it's done
    return cmd_node;
}
