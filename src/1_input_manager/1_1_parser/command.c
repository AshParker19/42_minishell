/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:11 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/17 19:45:48 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   main function for command case
 *          check BNF notation for the better understanding
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
	free_ast_v2(mbox->tmp_node);
	return (NULL);
}
