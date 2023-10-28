/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:11 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/28 17:03:48 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_ast *command_main(t_mbox *mbox)
{
    mbox->tmp_node = ast_create_node(CMD_NODE);
    token_list_main(mbox);    
    if(mbox->tmp_node &&
        (mbox->tmp_node->content || mbox->tmp_node->left))
    {
        return(mbox->tmp_node);
    }
    free_ast_v2(mbox->tmp_node);
    return(NULL);
}
