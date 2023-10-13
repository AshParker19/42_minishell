/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:27 by astein            #+#    #+#             */
/*   Updated: 2023/10/13 18:47:14 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_use_pipe(t_minibox *minibox, int status)
{
    if (status == SINGLE_CMD)
    {
        minibox->executor.io.use_pipe[CMD_IN] = ft_false;
        minibox->executor.io.use_pipe[CMD_OUT] = ft_false;
    }
    else if (status == FIRST_CMD)
    {
        minibox->executor.io.use_pipe[CMD_IN] = ft_false;
        minibox->executor.io.use_pipe[CMD_OUT] = ft_true;
    }
    else if (status == MIDDLE_CMD)
    {
        minibox->executor.io.use_pipe[CMD_IN] = ft_true;
        minibox->executor.io.use_pipe[CMD_OUT] = ft_true;
    }
    else if (status == LAST_CMD)
    {
        minibox->executor.io.use_pipe[CMD_IN] = ft_true;
        minibox->executor.io.use_pipe[CMD_OUT] = ft_false;
    }
}

void    setup_pipes(t_minibox *minibox)
{
    if (minibox->executor.io.use_pipe[CMD_IN])
        minibox->executor.io.dup_fd[CMD_IN]
        = dup2(minibox->executor.io.cmd_fd[CMD_IN], STDIN_FILENO);
    
    if (minibox->executor.io.use_pipe[CMD_OUT])
        minibox->executor.io.dup_fd[CMD_OUT]
        = dup2(minibox->executor.io.cmd_fd[CMD_OUT], STDOUT_FILENO);
}
