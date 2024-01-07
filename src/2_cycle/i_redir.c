/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:45:19 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 12:45:33 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief	initializes all the FDs as -1 so it's easy to check later on
 * 			if the were open
 * 
 * @param	mbox 
 */
void	initialize_fds(t_mbox *mbox, t_ast *cur, int cmd_pos)
{
	mbox->exec.io.cmd_fd[CMD_IN] = -1;
	mbox->exec.io.cmd_fd[CMD_OUT] = -1;
	mbox->exec.io.dup_fd[CMD_IN] = -1;
	mbox->exec.io.dup_fd[CMD_OUT] = -1;
	if (cur)
		cur->cmd_pos = cmd_pos;
}
