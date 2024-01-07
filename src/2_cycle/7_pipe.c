/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:02:07 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 14:29:32 by astein           ###   ########.fr       */
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

/**
 * @brief	close all FDs of current cycle
 * 
 * 			NOTE: function should only be called by 'free_cycle'
 * 
 * @param mbox 
 */
void	close_fds(t_mbox *mbox)
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
 * @brief   according to the accepted status sets the bool values in use_pipe[]
 *          if
 *              - we need read/write end in this case sets bool as ft_true
 *          else
 *              - false
 * 
 * @param   mbox 
 * @param   status 
 */
void	conf_pipe(t_mbox *mbox, int status)
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
void	redir_pipe(t_mbox *mbox, int *cur_pipe)
{
	if (mbox->exec.io.use_pipe[CMD_IN])
		mbox->exec.io.cmd_fd[CMD_IN] = mbox->exec.io.prev_pipe[P_RIGHT];
	if (mbox->exec.io.use_pipe[CMD_OUT])
		mbox->exec.io.cmd_fd[CMD_OUT] = cur_pipe[P_LEFT];
}

void	connect_child_fds(t_mbox *mbox)
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

