/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:27 by astein            #+#    #+#             */
/*   Updated: 2023/10/12 14:36:03 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_use_pipe(t_minibox *minibox, int status)
{
    if (status == SINGLE_CMD)
    {
        minibox->executor.io.use_pipe[READ_END] = ft_false;
        minibox->executor.io.use_pipe[WRITE_END] = ft_false;
    }
    else if (status == FIRST_CMD)
    {
        minibox->executor.io.use_pipe[READ_END] = ft_false;
        minibox->executor.io.use_pipe[WRITE_END] = ft_true;
    }
    else if (status == MIDDLE_CMD)
    {
        minibox->executor.io.use_pipe[READ_END] = ft_true;
        minibox->executor.io.use_pipe[WRITE_END] = ft_true;
    }
    else if (status == LAST_CMD)
    {
        minibox->executor.io.use_pipe[READ_END] = ft_true;
        minibox->executor.io.use_pipe[WRITE_END] = ft_false;
    }
}

void    setup_pipes(t_minibox *minibox)
{
    if (minibox->executor.io.use_pipe[READ_END])
        minibox->executor.io.dup_fd[READ_END]
        = dup2(minibox->executor.io.fd[READ_END], STDIN_FILENO);
    if (minibox->executor.io.use_pipe[WRITE_END])
        minibox->executor.io.dup_fd[WRITE_END]
        = dup2(minibox->executor.io.fd[WRITE_END], STDOUT_FILENO);
}

