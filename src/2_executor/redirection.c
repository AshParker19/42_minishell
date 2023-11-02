/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:47:15 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/02 13:08:24 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static   t_bool error_exit_child(t_mbox *mbox)
{
    create_error_msg("nn", ERR_PROMT, strerror(errno)); //FIXME: prints some crap to the terminal
    // if (mbox->executor.pid_index != -1)
        // exit(EXIT_FAILURE); //TODO: Handle errors
    return (ft_false);
}

static t_bool    handle_redir(t_mbox *mbox, t_ast *redir_node, int *in_fd, int *out_fd)
{
    if (redir_node->type == RED_IN)
    {
        if (*in_fd != -1)
            close(*in_fd);
        *in_fd = open(redir_node->content, O_RDONLY, 0666);
        if (*in_fd == -1)
            return (error_exit_child(mbox));
    }
    else if (redir_node->type == RED_IN_HD)
    {
        if (*in_fd != -1)
            close (*in_fd);
        if(heredoc(mbox, redir_node, in_fd) != 0)
            return (error_exit_child(mbox));
            //TODO: if return 1 - handle errors
        if (*in_fd == -1)
            return (error_exit_child(mbox));
    }
    else if (redir_node->type == RED_OUT_TR)
    {
        if (*out_fd != -1)
            close(*out_fd);
        *out_fd = open(redir_node->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (*out_fd == -1)
            return (error_exit_child(mbox));
    }
    else if (redir_node->type == RED_OUT_AP)
    {
        if (*out_fd != -1)
            close(*out_fd);
        *out_fd = open(redir_node->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
            return (error_exit_child(mbox));
    }
    return (ft_true);
}

/*
returns if file could be opened correct
*/
t_bool    setup_redir(t_mbox *mbox, t_ast *redir_node)
{
    int     in_fd;
    int     out_fd;
    t_ast   *tmp;

    tmp = redir_node;
    in_fd = -1;
    out_fd = -1;
    while (tmp)
    {
        if (!handle_redir(mbox, tmp, &in_fd, &out_fd))
            return (ft_false);
        tmp = tmp->left;
    }
    if (in_fd != -1)
    {
        if (mbox->executor.io.cmd_fd[CMD_IN] != -1 && mbox->executor.io.cmd_fd[CMD_IN] != STDIN_FILENO)
            close(mbox->executor.io.cmd_fd[CMD_IN]);
        mbox->executor.io.cmd_fd[CMD_IN] = in_fd;
    }
    if (out_fd != -1)
    {
        if (mbox->executor.io.cmd_fd[CMD_OUT] != -1 && mbox->executor.io.cmd_fd[CMD_OUT] != STDOUT_FILENO)
            close(mbox->executor.io.cmd_fd[CMD_OUT]);
        mbox->executor.io.cmd_fd[CMD_OUT] = out_fd;
    }
    return (ft_true);
}
