/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:46 by astein            #+#    #+#             */
/*   Updated: 2023/10/20 20:40:13 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_minibox *minibox, t_tree *arg_node)
{
	char	*error_msg;
	t_var	*cur;

	if (arg_node)
		create_error_msg("nnn", "env: ‘", arg_node->content,
			"’: No such file or directory");
	else
	{
		cur = minibox->vars;
		while (cur)
		{
			ft_putstr_fd(cur->key, 1);
			ft_putchar_fd('=', 1);
			if (cur->value)
				ft_putstr_fd(cur->value, 1);
			ft_putchar_fd('\n', 1);
			cur = cur->next;
		}
	}
}
