/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:55 by astein            #+#    #+#             */
/*   Updated: 2023/10/27 15:13:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_mbox *mbox, t_tree *arg_node)
{
	(void) mbox;
    (void) arg_node;
	// char	*pwd;

	// pwd = getcwd(NULL, 0);
	ft_putendl_fd(get_var_value(mbox, "PWD"), 1);
	// free(pwd);
}
