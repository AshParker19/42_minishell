/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:11 by anshovah          #+#    #+#             */
/*   Updated: 2024/01/06 19:29:49 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   main function for command case
 * 
 *          <command>      : <token list>           
 *			               ;
 * 
 * @param mbox 
 * @return t_ast* 
 */
t_ast	*command_main(t_mbox *mbox)
{
	mbox->tmp_node = ast_create_node(CMD_NODE);
	token_list_main(mbox);
	if (mbox->tmp_node && (mbox->tmp_node->content || mbox->tmp_node->left))
		return (mbox->tmp_node);
	free_ast(mbox->tmp_node);
	return (NULL);
}
