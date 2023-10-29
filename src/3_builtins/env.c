/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:46 by astein            #+#    #+#             */
/*   Updated: 2023/10/29 00:56:01 by astein           ###   ########.fr       */
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
 * @param	mbox 
 * @param	arg_node 
 */
void	builtin_env(t_mbox *mbox, t_ast *arg_node)
{
	char	*error_msg;
	t_env_var	*cur;

	if (arg_node)
		create_error_msg("nnn", "env: ‘", arg_node->content,
			"’: No such file or directory");
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
