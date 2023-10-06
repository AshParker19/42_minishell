/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:11 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/06 11:41:20 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_tree *command_main(t_minibox *minibox)
{
    // TODO:
    minibox->tmp_node = ast_create_node(CMD_NODE);
    token_list_main(minibox);    
    if(minibox->tmp_node &&
        (minibox->tmp_node->content || minibox->tmp_node->left))
    {
        return(minibox->tmp_node);
    }
    delete_ast(minibox->tmp_node);
    return(NULL);
}
