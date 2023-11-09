/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:46 by astein            #+#    #+#             */
/*   Updated: 2023/11/08 22:12:25 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	prints all key-value pairs of the t_env_var ll
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
	t_env_var	*cur;

	if (arg_node)
	{
		put_err_msg("nnn", "env: ‘", arg_node->content,
			"’: No such file or directory");
		set_var_value(mbox, "?", EXIT_STR_FAILURE); // shouldnt be here, return false instead
	}
	else
	{
		cur = mbox->env_vars;
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
	}
}
