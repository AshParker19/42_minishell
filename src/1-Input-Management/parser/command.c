/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:11 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/02 18:46:03 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_tree *command(t_minibox *minibox)
{
    t_tree  *cmd_node;

    cmd_node = ast_create_node(CMD_NODE);
    if (!cmd_node)
        return (NULL);
    minibox->tmp_node = cmd_node;
    token_list(minibox);
    if (cmd_node && !minibox->tmp_node->content)
    {
        delete_ast(minibox->tmp_node);
        return (NULL);
    }
    minibox->root = minibox->tmp_node;
    return cmd_node;
}
