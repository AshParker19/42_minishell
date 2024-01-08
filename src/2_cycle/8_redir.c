/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:45:19 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 22:53:58 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/docs/documentation.md#setup-redirections
 */

#include "frankenshell.h"

static t_bool	create_open_file_err(t_mbox *mbox, char *fn)
{
	err_msg(mbox, NO_EXIT_STATUS, "nnnn", ERR_P, fn, CS, strerror(errno));
	return (ft_false);
}

/**
 * @brief   Called if an in redirection needs to be setup. 
 * 			
 * 	CASE: OPEN
 *		It tries to open the file and if it fails it will create an
 * 		error message and returns ft_false.
 * 
 * CASE: HEREDOC
 * 		The heredoc will be setup via 'setup_hd'. If it fails it will
 * 		return ft_false.
 * 			
 * 
 * @param   mbox        
 * @param   redir_node  
 * @param   cur_p       
 * @return  t_bool      
 */
static t_bool	conf_redir_in(t_mbox *mbox, t_ast *redir_node, int *cur_p)
{
	int	*in_fd;

	in_fd = &mbox->exec.io.cmd_fd[CMD_IN];
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
		if (!setup_hd(mbox, redir_node, cur_p))
			return (ft_false);
	}
	return (ft_true);
}

/**
 * @brief   Called if an out redirection needs to be setup. It tries to open
 * 			the file and if it fails it will create an error message and returns
 * 			ft_false.
 * 
 * @param   mbox        
 * @param   redir_node  
 * @return  t_bool      
 */
static t_bool	conf_redir_out(t_mbox *mbox, t_ast *redir_node)
{
	int	*out;

	out = &mbox->exec.io.cmd_fd[CMD_OUT];
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

/**
 * @brief	A loop will traverse trough the redir_node and setup all the
 * 			redirects.
 * 
 * @param   mbox        
 * @param   redir_node  
 * @param   cur_p       
 * @return  t_bool      if config was successful
 */
static t_bool	conf_redir(t_mbox *mbox, t_ast *redir_node, int *cur_p)
{
	t_ast	*tmp;

	tmp = redir_node;
	while (tmp)
	{
		if (tmp->type == RED_IN || tmp->type == RED_IN_HD)
		{
			if (!conf_redir_in(mbox, tmp, cur_p))
				return (ft_false);
		}
		else if (tmp->type == RED_OUT_TR || tmp->type == RED_OUT_AP)
		{
			if (!conf_redir_out(mbox, tmp))
				return (ft_false);
		}
		tmp = tmp->left;
	}
	return (ft_true);
}

/**
 * @brief   According to the parameter redir_node the redirections will be setup
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/docs/documentation.md#setup-redirections
 * 
 * @param   mbox        
 * @param   redir_node  
 * @param   cur_p       fd of current pipe
 * @return  t_bool      if setup was successful
 */
t_bool	setup_redirs(t_mbox *mbox, t_ast *redir_node, int *cur_p)
{
	if (!conf_redir(mbox, redir_node, cur_p))
	{
		if (g_signal_status != SIGNAL_EXIT_HD)
			set_var_value_int(mbox, "?", EXIT_FAILURE);
		return (ft_false);
	}
	return (ft_true);
}
