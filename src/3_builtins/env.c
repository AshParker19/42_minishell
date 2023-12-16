/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:46 by astein            #+#    #+#             */
/*   Updated: 2023/12/16 13:06:31 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   The builtin `env` outputs all variable key-value pairs of the linked
 * 			list like `key=value\n`
 * 
 * 			ARGUMENTS:
 * 			if the cmd has an 'arg_node' it prints an error instead
 * 
 * 			NOTE:
 * 			the key '?' which represents the latest exit status won't be printed
 *
 * 			USEFUL:
 * 				env -i ./minishell 			--> no env vars will be loaded
 * 				env -u "NAME" ./minishell 	--> no key NAME will be in env
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#env
 * 
 * @param   mbox        
 * @param   arg_node    
 */
void	builtin_env(t_mbox *mbox, t_ast *arg_node)
{
	t_env	*cur;

	if (arg_node)
		err_msg(mbox, 127, "nnnn", "env: ‘", arg_node->content, "’: ", NO_FOD);
	else
	{
		cur = mbox->env;
		while (cur)
		{
			if (!str_cmp_strct(cur->key, "?"))
			{
				ft_putstr_fd(cur->key, mbox->executor.io.cmd_fd[CMD_OUT]);
				ft_putchar_fd('=', mbox->executor.io.cmd_fd[CMD_OUT]);
				if (cur->value)
					ft_putstr_fd(cur->value, mbox->executor.io.cmd_fd[CMD_OUT]);
				ft_putchar_fd('\n', mbox->executor.io.cmd_fd[CMD_OUT]);
			}
			cur = cur->next;
		}
		set_var_value_int(mbox, "?", EXIT_SUCCESS);
	}
}
