/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:39 by astein            #+#    #+#             */
/*   Updated: 2023/10/28 19:07:41 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"





int		cmd_counter(t_ast *ast_node)
{
	if(!ast_node)
		return (0);
	if (ast_node->type == CMD_NODE)
		return (1);
	return (1 + cmd_counter(ast_node->right));	
}

void	initialize_io(t_mbox *mbox)
{	
	mbox->executor.io.cmd_fd[CMD_IN] = -1;
	mbox->executor.io.cmd_fd[CMD_OUT] = -1;
	mbox->executor.io.dup_fd[CMD_IN] = -1;
	mbox->executor.io.dup_fd[CMD_OUT] = -1;
}



/* Print the ouput of the AST built by the Parser*/
void	print_executor_output(t_mbox *mbox, int i)
{
    (void)mbox;
	if(i == 0)
	{
		printf("\n ------------------------------------ \n");
		printf("|              EXECUTOR              |\n");
		printf("|           cmd count: %d             |\n",cmd_counter(mbox->root));
		printf(" ------------------------------------ \n");	
	}
	else
		printf(" ------------------------------------ \n");
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
	if (mbox->executor.io.cmd_fd[CMD_IN] != -1)
		close (mbox->executor.io.cmd_fd[CMD_IN]);	
	if (mbox->executor.io.cmd_fd[CMD_OUT] != -1)
		close (mbox->executor.io.cmd_fd[CMD_OUT]);
	if (mbox->executor.io.dup_fd[CMD_IN] != -1)
		close (mbox->executor.io.dup_fd[CMD_IN]);
	if (mbox->executor.io.dup_fd[CMD_OUT] != -1)
		close (mbox->executor.io.dup_fd[CMD_OUT]);
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
	if (mbox->executor.pid)
	{
		free (mbox->executor.pid);
		mbox->executor.pid = NULL;
	}
	if (mbox->executor.cmd_av)
	{
		free_whatever("m", mbox->executor.cmd_av);
		mbox->executor.cmd_av = NULL;
	}
}
