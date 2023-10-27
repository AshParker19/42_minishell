/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:27 by astein            #+#    #+#             */
/*   Updated: 2023/10/27 15:13:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void    setup_pipes(t_mbox *mbox, int *cur_pipe)
{
    if (mbox->executor.io.use_pipe[CMD_IN])
        mbox->executor.io.cmd_fd[CMD_IN]
            = mbox->executor.io.prev_pipe[P_RIGHT];
    if (mbox->executor.io.use_pipe[CMD_OUT])
        mbox->executor.io.cmd_fd[CMD_OUT] = cur_pipe[P_LEFT];
}

void    setup_process_std(t_mbox *mbox)
{
    if (mbox->executor.io.cmd_fd[CMD_IN] != -1)
        mbox->executor.io.dup_fd[CMD_IN]
            = dup2(mbox->executor.io.cmd_fd[CMD_IN], STDIN_FILENO);
    if (mbox->executor.io.cmd_fd[CMD_OUT] != -1)
        mbox->executor.io.dup_fd[CMD_OUT]
            = dup2(mbox->executor.io.cmd_fd[CMD_OUT], STDOUT_FILENO);
}
