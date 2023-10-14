/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:55 by astein            #+#    #+#             */
/*   Updated: 2023/10/14 19:06:30 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_minibox *minibox, t_tree *arg_node)
{
	(void) minibox;
    (void) arg_node;
	// char	*pwd;

	// pwd = getcwd(NULL, 0);
	ft_putendl_fd(get_var_value(minibox, "PWD"), 1);
	// free(pwd);
}
