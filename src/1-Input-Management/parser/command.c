/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:11 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/27 15:13:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_tree *command_main(t_mbox *mbox)
{
    mbox->tmp_node = ast_create_node(CMD_NODE);
    token_list_main(mbox);    
    if(mbox->tmp_node &&
        (mbox->tmp_node->content || mbox->tmp_node->left))
    {
        return(mbox->tmp_node);
    }
    delete_ast(mbox->tmp_node);
    return(NULL);
}
