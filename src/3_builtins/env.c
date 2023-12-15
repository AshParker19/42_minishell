/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:46 by astein            #+#    #+#             */
/*   Updated: 2023/12/15 13:44:37 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	prints all key-value pairs of the t_env ll
 * 
 * 			if the cmd will have an 'arg_node' prints an error instead
 * 			NOTE:
 * 			the key '?' which represents the latest exit status won't be printed
 *
 * 			USEFUL:
 * 				env -i ./minishell --> no env vars will be loaded
 * 				env -u "NAME" ./minishell --> no NAME will be in env
 * @param	mbox 
 * @param	arg_node 
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
		set_var_value(mbox, "?", EXIT_SUCCESS_STR);
	}
}
