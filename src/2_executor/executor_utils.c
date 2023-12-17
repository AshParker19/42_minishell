/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:39 by astein            #+#    #+#             */
/*   Updated: 2023/12/17 16:58:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief	recursively traverses through the AST and counts the amount
 * 			of command nodes
 * 
 * @param	ast_node 
 * @return	int 
 */
int	cmd_counter(t_ast *ast_node)
{
	if (!ast_node)
		return (0);
	if (ast_node->type == CMD_NODE)
		return (1);
	return (1 + cmd_counter(ast_node->right));
}

/**
 * @brief	initializes all the FDs as -1 so it's easy to check later on
 * 			if the were open
 * 
 * @param	mbox 
 */
void	initialize_io(t_mbox *mbox, t_ast *cur, int cmd_pos)
{
	mbox->exec.io.cmd_fd[CMD_IN] = -1;
	mbox->exec.io.cmd_fd[CMD_OUT] = -1;
	mbox->exec.io.dup_fd[CMD_IN] = -1;
	mbox->exec.io.dup_fd[CMD_OUT] = -1;
	if (cur)
		cur->cmd_pos = cmd_pos;
}

/**
 * @brief	close all FDs of current cycle
 * 
 * 			NOTE: function should only be called by 'free_cycle'
 * 
 * @param mbox 
 */
void	close_process_fds_v2(t_mbox *mbox)
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
 * @brief	frees and NULLs in mbox:
 * 				- cmd_av
 * 				- pid
 * 				
 *
 * 			NOTE: function should only be called by 'free_cycle'
 * 
 * @param 	mbox 
 */
void	free_process_v2(t_mbox *mbox)
{
	if (mbox->exec.pid)
	{
		free (mbox->exec.pid);
		mbox->exec.pid = NULL;
	}
}

t_bool	allocate_pid_array(t_mbox *mbox)
{
	print_executor_output(mbox, ft_true);
	mbox->exec.pid = ft_calloc(cmd_counter(mbox->ast), sizeof(int));
	if (!mbox->exec.pid)
		return (ft_false);
	return (ft_true);
}
