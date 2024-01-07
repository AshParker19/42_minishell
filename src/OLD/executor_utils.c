/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:39 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 12:50:22 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"


/**
 * @brief	close all FDs of current cycle
 * 
 * 			NOTE: function should only be called by 'free_cycle'
 * 
 * @param mbox 
 */
void	close_process_fds_v2(t_mbox *mbox)
{
	if (mbox->exec.io.cmd_fd[CMD_IN] != -1)
		close (mbox->exec.io.cmd_fd[CMD_IN]);
	if (mbox->exec.io.cmd_fd[CMD_OUT] != -1)
		close (mbox->exec.io.cmd_fd[CMD_OUT]);
	if (mbox->exec.io.dup_fd[CMD_IN] != -1)
		close (mbox->exec.io.dup_fd[CMD_IN]);
	if (mbox->exec.io.dup_fd[CMD_OUT] != -1)
		close (mbox->exec.io.dup_fd[CMD_OUT]);
}

/**
 * @brief	frees and NULLs in mbox:
 * 				- cmd_av
 * 				- pid
 * 				
 *
 * 			NOTE: function should only be called by 'free_cycle'
 * 
 * @param 	mbox 
 */
void	free_process_v2(t_mbox *mbox)
{
	if (mbox->exec.pid)
	{
		free (mbox->exec.pid);
		mbox->exec.pid = NULL;
	}
}


