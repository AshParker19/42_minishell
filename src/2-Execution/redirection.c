/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:47:15 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/18 16:21:52 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    handle_redir(t_tree *redir_node, int *in_fd, int *out_fd)
{
    if (redir_node->type == RED_IN)
    {
        if (*in_fd != -1)
            close(*in_fd);
        *in_fd = open(redir_node->content, O_RDONLY, 0666);
        if (*in_fd == -1)
            exit(EXIT_FAILURE); //TODO: Handle errors
    }
    else if (redir_node->type == RED_IN_HD)
    {
        if (*in_fd != -1)
            close (*in_fd);
        heredoc(redir_node, in_fd, NULL); //TODO: if return 1 - handle errors
        if (*in_fd == -1)
            exit(EXIT_FAILURE);
    }
    else if (redir_node->type == RED_OUT_TR)
    {
        if (*out_fd != -1)
            close(*out_fd);
        *out_fd = open(redir_node->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (*out_fd == -1)
            exit(EXIT_FAILURE); //TODO: Handle errors
    }
    else if (redir_node->type == RED_OUT_AP)
    {
        if (*out_fd != -1)
            close(*out_fd);
        *out_fd = open(redir_node->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (*out_fd == -1)
            exit (EXIT_FAILURE);    
    }
}

void    setup_redir(t_minibox *minibox, t_tree *redir_node)
{
    int in_fd;
    int out_fd;
    t_tree *tmp;

    tmp = redir_node;
    in_fd = -1;
    out_fd = -1;
    while (tmp)
    {
        handle_redir(tmp, &in_fd, &out_fd);
        tmp = tmp->left;
    }
    if (in_fd != -1)
    {
        if (minibox->executor.io.cmd_fd[CMD_IN] != -1)
            close(minibox->executor.io.cmd_fd[CMD_IN]);
        minibox->executor.io.cmd_fd[CMD_IN] = in_fd;
    }
    if (out_fd != -1)
    {
        if (minibox->executor.io.cmd_fd[CMD_OUT] != -1)
            close(minibox->executor.io.cmd_fd[CMD_OUT]);
        minibox->executor.io.cmd_fd[CMD_OUT] = out_fd;
    }
}
