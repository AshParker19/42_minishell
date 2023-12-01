/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:27 by astein            #+#    #+#             */
/*   Updated: 2023/12/01 16:11:21 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		mbox->executor.io.use_pipe[CMD_IN] = ft_false;
		mbox->executor.io.use_pipe[CMD_OUT] = ft_false;
	}
	else if (status == FIRST_CMD)
	{
		mbox->executor.io.use_pipe[CMD_IN] = ft_false;
		mbox->executor.io.use_pipe[CMD_OUT] = ft_true;
	}
	else if (status == MIDDLE_CMD)
	{
		mbox->executor.io.use_pipe[CMD_IN] = ft_true;
		mbox->executor.io.use_pipe[CMD_OUT] = ft_true;
	}
	else if (status == LAST_CMD)
	{
		mbox->executor.io.use_pipe[CMD_IN] = ft_true;
		mbox->executor.io.use_pipe[CMD_OUT] = ft_false;
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
	if (mbox->executor.io.use_pipe[CMD_IN])
		mbox->executor.io.cmd_fd[CMD_IN] = mbox->executor.io.prev_pipe[P_RIGHT];
	if (mbox->executor.io.use_pipe[CMD_OUT])
		mbox->executor.io.cmd_fd[CMD_OUT] = cur_pipe[P_LEFT];
}

void	setup_process_std(t_mbox *mbox) //TODO: rename it 
{
	if (mbox->executor.io.cmd_fd[CMD_IN] != -1)
	{
		mbox->executor.io.dup_fd[CMD_IN]
			= dup2(mbox->executor.io.cmd_fd[CMD_IN], STDIN_FILENO);
		if (mbox->executor.io.dup_fd[CMD_IN] < 0)
			err_free_and_close_box(mbox, EXIT_FAILURE);
	}
	if (mbox->executor.io.cmd_fd[CMD_OUT] != -1)
	{
		mbox->executor.io.dup_fd[CMD_OUT]
			= dup2(mbox->executor.io.cmd_fd[CMD_OUT], STDOUT_FILENO);
		if (mbox->executor.io.dup_fd[CMD_OUT] < 0)
			err_free_and_close_box(mbox, EXIT_FAILURE); // TODO: we should exit from the whole program not only child process
	}
}
