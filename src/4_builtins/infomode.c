/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infomode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 01:46:12 by astein            #+#    #+#             */
/*   Updated: 2023/12/18 02:04:55 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   toggle the info mode on and off
 *
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#infomode-builtin
 * 
 * @param   mbox        
 * @param   arg_node    
 */
void	builtin_infomode(t_mbox *mbox, t_ast *arg_node)
{
	(void)arg_node;
	if (!mbox)
		return ;
	if (mbox->info_mode)
	{
		info_put_banner(mbox, "INFO MODE DEACTIVATED!", NULL, RED);
		mbox->info_mode = ft_false;
	}
	else
	{
		mbox->info_mode = ft_true;
		info_put_banner(mbox, "INFO MODE ACTIVATED!", NULL, GREEN);
	}
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
}
