/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:25 by astein            #+#    #+#             */
/*   Updated: 2023/12/15 14:16:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   traverses through the arguments of arg_node and deletes
 *          the corresponding nodes from the t_env ll 
 * 
 * @param   mbox 
 * @param   arg_node 
 */
void	builtin_unset(t_mbox *mbox, t_ast *arg_node)
{
	while (arg_node)
	{
		delete_var(mbox, arg_node->content);
		arg_node = arg_node->right;
	}
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
}
