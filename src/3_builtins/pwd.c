/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:55 by astein            #+#    #+#             */
/*   Updated: 2023/11/11 16:29:33 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	acceses the value PWD from the ll and writs to the correct FD
 * 			like in shell all arguments will be ignored
 * 
 * @param	mbox 
 * @param	arg_node 
 */
void	builtin_pwd(t_mbox *mbox, t_ast *arg_node)
{
    (void) arg_node;

	ft_putendl_fd(getcwd(NULL, 0), mbox->executor.io.cmd_fd[CMD_OUT]);
	set_var_value(mbox, "?", EXIT_STR_SUCCESS);
}

