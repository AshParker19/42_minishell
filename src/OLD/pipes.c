/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:27 by astein            #+#    #+#             */
/*   Updated: 2023/12/17 16:56:25 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   according to the accepted status sets the bool values in use_pipe[]
 *          if
 *              - we need read/write end in this case sets bool as ft_true
 *          else
 *              - false
 * 
 * @param   mbox 
 * @param   status 
 */
void	setup_use_pipe(t_mbox *mbox, int status)
{
	if (status == SINGLE_CMD)
	{
		mbox->exec.io.use_pipe[CMD_IN] = ft_false;
		mbox->exec.io.use_pipe[CMD_OUT] = ft_false;
	}
	else if (status == FIRST_CMD)
	{
		mbox->exec.io.use_pipe[CMD_IN] = ft_false;
		mbox->exec.io.use_pipe[CMD_OUT] = ft_true;
	}
	else if (status == MIDDLE_CMD)
	{
		mbox->exec.io.use_pipe[CMD_IN] = ft_true;
		mbox->exec.io.use_pipe[CMD_OUT] = ft_true;
	}
	else if (status == LAST_CMD)
	{
		mbox->exec.io.use_pipe[CMD_IN] = ft_true;
		mbox->exec.io.use_pipe[CMD_OUT] = ft_false;
	}
}

/**
 * @brief   
 * 
 * @param   mbox 
 * @param   cur_pipe 
 */
void	setup_pipes(t_mbox *mbox, int *cur_pipe)
{
	if (mbox->exec.io.use_pipe[CMD_IN])
		mbox->exec.io.cmd_fd[CMD_IN] = mbox->exec.io.prev_pipe[P_RIGHT];
	if (mbox->exec.io.use_pipe[CMD_OUT])
		mbox->exec.io.cmd_fd[CMD_OUT] = cur_pipe[P_LEFT];
}

void	setup_process_std_tmp(t_mbox *mbox)
{
	if (mbox->exec.io.cmd_fd[CMD_IN] != -1)
	{
		mbox->exec.io.dup_fd[CMD_IN]
			= dup2(mbox->exec.io.cmd_fd[CMD_IN], STDIN_FILENO);
		if (mbox->exec.io.dup_fd[CMD_IN] < 0)
			destroy_mbox_with_exit(mbox, EXIT_FAILURE);
	}
	if (mbox->exec.io.cmd_fd[CMD_OUT] != -1)
	{
		mbox->exec.io.dup_fd[CMD_OUT]
			= dup2(mbox->exec.io.cmd_fd[CMD_OUT], STDOUT_FILENO);
		if (mbox->exec.io.dup_fd[CMD_OUT] < 0)
			destroy_mbox_with_exit(mbox, EXIT_FAILURE);
	}
}
