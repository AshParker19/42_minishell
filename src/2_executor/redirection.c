/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:47:15 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/15 14:16:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   here we dont need to exit because:
 *              - either we are not in a child
 *              - or the function 'exec_child' will exit the child properly
 *                  since we are pasing the ft_false all the way back there
 *                  so each funtion on the way has the posibillity to free all
 *                  allocated stuff
 * @param mbox 
 * @param fn        filename of the file causing the errror
 * @return t_bool 
 */
static t_bool	create_open_file_err(t_mbox *mbox, char *fn)
{
	err_msg(mbox, NO_EXIT_STATUS, "nnnn", ERR_P, fn, CS, strerror(errno));
	return (ft_false);
}

static t_bool	setup_redir_in(t_mbox *mbox, t_ast *redir_node, int *cur_p)
{
	int	*in_fd;

	in_fd = &mbox->executor.io.cmd_fd[CMD_IN];
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
		if (!heredoc(mbox, redir_node, cur_p))
			return (ft_false);
	}
	return (ft_true);
}

static t_bool	setup_redir_out(t_mbox *mbox, t_ast *redir_node)
{
	int	*out;

	out = &mbox->executor.io.cmd_fd[CMD_OUT];
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

static t_bool	redir_io(t_mbox *mbox, t_ast *redir_node, int *cur_p)
{
	t_ast	*tmp;

	tmp = redir_node;
	while (tmp)
	{
		if (tmp->type == RED_IN || tmp->type == RED_IN_HD)
		{
			if (!setup_redir_in(mbox, tmp, cur_p))
				return (ft_false);
		}
		else if (tmp->type == RED_OUT_TR || tmp->type == RED_OUT_AP)
		{
			if (!setup_redir_out(mbox, tmp))
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
t_bool	configure_redir(t_mbox *mbox, t_ast *redir_node, int *cur_p)
{
	if (!redir_io(mbox, redir_node, cur_p))
	{
		if (g_signal_status != SIGNAL_EXIT_HD)
			set_var_value_int(mbox, "?", EXIT_FAILURE);
		return (ft_false);
	}
	return (ft_true);
}
