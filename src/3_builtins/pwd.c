/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:55 by astein            #+#    #+#             */
/*   Updated: 2023/12/15 14:09:03 by astein           ###   ########.fr       */
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
	char	*temp;

	(void)arg_node;
	temp = NULL;
	temp = getcwd(NULL, 0);
	ft_putendl_fd(temp, mbox->executor.io.cmd_fd[CMD_OUT]);
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
	if (temp)
		free(temp);
}
