/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:47:15 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/12 16:35:20 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    handle_redir(t_tree *node, int *in_fd, int *out_fd)
{
    if (node->type == RED_IN)
    {
        if (*in_fd != -1)
            close(*in_fd);
        *in_fd = open(node->content, O_RDONLY, 0666);
        if (*in_fd == -1)
            exit(EXIT_FAILURE); //TODO: Handle errors
    }
    else if (node->type == RED_IN_HD)
    {

    }
    else if (node->type == RED_OUT_TR)
    {
        if (*out_fd != -1)
            close(*out_fd);
        *out_fd = open(node->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (*out_fd == -1)
            exit(EXIT_FAILURE); //TODO: Handle errors
    }
    else if (node->type == RED_OUT_AP)
    {
        if (*out_fd != -1)
            close(*out_fd);
        *out_fd = open(node->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (*out_fd == -1)
            exit (EXIT_FAILURE);    
    }
}

void    setup_redir(t_minibox *minibox)
{
    int in_fd;
    int out_fd;
    t_tree *tmp;

    tmp = minibox->executor.io.redir;
    in_fd = -1;
    out_fd = -1;
    while (tmp)
    {
        handle_redir(tmp, &in_fd, &out_fd);
        tmp = tmp->left;
    }
    if (in_fd != -1)
    {
        minibox->executor.io.dup_fd[READ_END] = dup2(in_fd, STDIN_FILENO);
        close (in_fd);
    }
    if (out_fd != -1)
    {
        minibox->executor.io.dup_fd[WRITE_END] = dup2(out_fd, STDOUT_FILENO);
        close (out_fd);
    }
}
