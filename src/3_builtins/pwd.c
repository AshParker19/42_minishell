/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:55 by astein            #+#    #+#             */
/*   Updated: 2023/10/29 00:29:27 by astein           ###   ########.fr       */
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

	ft_putendl_fd(get_var_value(mbox, "PWD"), mbox->executor.io.cmd_fd[CMD_OUT]);
}

