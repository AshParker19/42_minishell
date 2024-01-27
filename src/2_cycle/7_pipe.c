/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:02:07 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 22:45:40 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   Initializes all the FDs with -1 so it's easy to check later on
 * 			if the were open (so they need to be closed again)
 * 
 * @param   mbox        
 * @param   cur         
 * @param   cmd_pos     
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
 * @brief   According to the command position, booleans will be set.
 * 			Later this information will be used to determine which end of the
 * 			pipe will be used.
 * 
 * @param   mbox        
 * @param   cmd_pos      
 */
void	conf_pipe(t_mbox *mbox, int cmd_pos)
{
	if (cmd_pos == SINGLE_CMD)
	{
		mbox->exec.io.use_pipe[CMD_IN] = ft_false;
		mbox->exec.io.use_pipe[CMD_OUT] = ft_false;
	}
	else if (cmd_pos == FIRST_CMD)
	{
		mbox->exec.io.use_pipe[CMD_IN] = ft_false;
		mbox->exec.io.use_pipe[CMD_OUT] = ft_true;
	}
	else if (cmd_pos == MIDDLE_CMD)
	{
		mbox->exec.io.use_pipe[CMD_IN] = ft_true;
		mbox->exec.io.use_pipe[CMD_OUT] = ft_true;
	}
	else if (cmd_pos == LAST_CMD)
	{
		mbox->exec.io.use_pipe[CMD_IN] = ft_true;
		mbox->exec.io.use_pipe[CMD_OUT] = ft_false;
	}
}

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

