/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:55 by astein            #+#    #+#             */
/*   Updated: 2023/10/09 17:22:04 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(char *args)
{
	char	*pwd;

	(void)args; //TODO;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
