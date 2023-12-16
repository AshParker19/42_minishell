/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:55 by astein            #+#    #+#             */
/*   Updated: 2023/12/16 13:29:33 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   outputs the current wd using the external function 'getcwd'
 * 			like in bash all arguments will be ignored
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#pwd
 * @param   mbox        
 * @param   arg_node    
 */
void	builtin_pwd(t_mbox *mbox, t_ast *arg_node)
{
	char	*temp;

	(void)arg_node;
	temp = NULL;
	temp = getcwd(NULL, 0);
	ft_putendl_fd(temp, mbox->executor.io.cmd_fd[CMD_OUT]);
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
	if (temp)
		free(temp);
}
