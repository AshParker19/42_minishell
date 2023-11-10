/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:47:15 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/10 19:28:20 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief   here we dont need to exit because:
 *              - either we are not in a child
 *              - or the function 'perform_child' will exit the child properly
 *                  since we are pasing the ft_false all the way back there
 *                  so each funtion on the way has the posibillity to free all
 *                  allocated stuff
 * @param mbox 
 * @param fn        filename of the file causing the errror
 * @return t_bool 
 */
static   t_bool create_open_file_err(t_mbox *mbox, char *fn)
{
    (void) mbox; //TODO: check it
    put_err_msg("nnnn", ERR_PROMT, fn, ": ", strerror(errno)); //FIXME: prints some crap to the terminal
    return (ft_false);
}

static  t_bool setup_redir_in(t_mbox *mbox, t_ast *redir_node, int *in_fd)
{
    if (redir_node->type == RED_IN)
    {
        if (*in_fd != -1)
            close(*in_fd);
        *in_fd = open(redir_node->content, O_RDONLY, 0666);
        if (*in_fd == -1)
            return (create_open_file_err(mbox, redir_node->content));
    }
    else if (redir_node->type == RED_IN_HD)
    {
        if (*in_fd != -1)
            close (*in_fd);
        if (!heredoc(mbox, redir_node, in_fd))
		{
			g_signal_status = SIGNAL_HEREDOC;
			return (ft_false);
		}
    }
    return (ft_true);
}

static t_bool   setup_redir_out(t_mbox *mbox, t_ast *redir_node, int *out)
{
    if (redir_node->type == RED_OUT_TR)
    {
        if (*out != -1)
            close(*out);
        *out = open(redir_node->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (*out == -1)
            return (create_open_file_err(mbox, redir_node->content));
    }
    else if (redir_node->type == RED_OUT_AP)
    {
        if (*out != -1)
            close(*out);
        *out = open(redir_node->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (*out == -1)
            return (create_open_file_err(mbox, redir_node->content));
    }
    return (ft_true);
}

static t_bool   redir_io(t_mbox *mbox, t_ast *redir_node, int *in, int *out)
{
    t_ast   *tmp;

    tmp = redir_node;
    while (tmp)
    {
        if (tmp->type == RED_IN || tmp->type == RED_IN_HD)
        {
            if (!setup_redir_in(mbox, tmp, in)) // can I do return(setup_redir_in(mbox, tmp, in))?
                return (ft_false);
        }
        else if (tmp->type == RED_OUT_TR
            || tmp->type == RED_OUT_AP)
        {
            if (!setup_redir_out(mbox, tmp, out))
                return (ft_false);
        }    
        tmp = tmp->left;
    }
    return (ft_true);
}

/**
 * @brief   accept a 'redir_node' and sets up the redirections accordingly
 *          to the result of 'redir_io'
 *          
 *          retunrs ft_false if any errors related to opening files occured
 * 
 * @param   mbox 
 * @param   redir_node 
 * @return  t_bool 
 */
t_bool    configure_redir(t_mbox *mbox, t_ast *redir_node)
{
    int     in_fd;
    int     out_fd;

    in_fd = -1;
    out_fd = -1;
    if (!redir_io(mbox, redir_node, &in_fd, &out_fd))
    {
        set_var_value(mbox, "?", EXIT_STR_FAILURE); //FIXME: wrong for heredoc
        return (ft_false);
    }
    if (in_fd != -1)
    {
        if (mbox->executor.io.cmd_fd[CMD_IN] != -1
            && mbox->executor.io.cmd_fd[CMD_IN] != STDIN_FILENO)
            close(mbox->executor.io.cmd_fd[CMD_IN]);
        mbox->executor.io.cmd_fd[CMD_IN] = in_fd;
    }
    if (out_fd != -1)
    {
        if (mbox->executor.io.cmd_fd[CMD_OUT] != -1
            && mbox->executor.io.cmd_fd[CMD_OUT] != STDOUT_FILENO)
            close(mbox->executor.io.cmd_fd[CMD_OUT]);
        mbox->executor.io.cmd_fd[CMD_OUT] = out_fd;
    }
    return (ft_true);
}
