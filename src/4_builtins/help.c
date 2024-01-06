/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 02:23:37 by astein            #+#    #+#             */
/*   Updated: 2023/12/18 02:31:33 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

void	builtin_help(t_mbox *mbox, t_ast *arg_node)
{
	(void)mbox;
	(void)arg_node;
	system("xdg-open https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md >/dev/null 2>&1 &");	
}
