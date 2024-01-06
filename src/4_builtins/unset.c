/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:25 by astein            #+#    #+#             */
/*   Updated: 2023/12/18 02:05:44 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   The builtin 'unset' deletes the corresponding nodes from the `t_env`
 * 			ll via the 'unset_var' function.
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#unset-builtin
 * 
 * @param   mbox        
 * @param   arg_node    
 */
void	builtin_unset(t_mbox *mbox, t_ast *arg_node)
{
	while (arg_node)
	{
		unset_var(mbox, arg_node->content);
		arg_node = arg_node->right;
	}
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
}
