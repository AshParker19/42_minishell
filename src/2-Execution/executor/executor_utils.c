/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:39 by astein            #+#    #+#             */
/*   Updated: 2023/10/28 15:37:23 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void reset_executor(t_mbox *mbox)
{
	mbox->executor.cmd_av = NULL;
	mbox->executor.io.prev_pipe[P_LEFT] = -1;
	mbox->executor.io.prev_pipe[P_RIGHT] = -1;
	mbox->executor.pid_index = 0;
	mbox->executor.pid = NULL;
}

void load_executor(t_mbox *mbox)
{
	
	initialize_builtins(mbox);
}

int		cmd_counter(t_tree *tree_node)
{
	if(!tree_node)
		return (0);
	if (tree_node->type == CMD_NODE)
		return (1);
	return (1 + cmd_counter(tree_node->right));	
}

void	initialize_io(t_mbox *mbox)
{	
	mbox->executor.io.cmd_fd[CMD_IN] = -1;
	mbox->executor.io.cmd_fd[CMD_OUT] = -1;
	mbox->executor.io.dup_fd[CMD_IN] = -1;
	mbox->executor.io.dup_fd[CMD_OUT] = -1;
}

void	free_process(t_mbox *mbox)
{
	// TODO: DOUBLE CHECK IF RIGHT
	if (mbox->executor.cmd_av)
	{
		free_whatever("m", mbox->executor.cmd_av);
		mbox->executor.cmd_av = NULL;
	}
	if (mbox->executor.io.cmd_fd[CMD_IN] != -1)
		close (mbox->executor.io.cmd_fd[CMD_IN]);	
	if (mbox->executor.io.cmd_fd[CMD_OUT] != -1)
		close (mbox->executor.io.cmd_fd[CMD_OUT]);
	if (mbox->executor.io.dup_fd[CMD_IN] != -1)
		close (mbox->executor.io.dup_fd[CMD_IN]);
	if (mbox->executor.io.dup_fd[CMD_OUT] != -1)
		close (mbox->executor.io.dup_fd[CMD_OUT]);
	// if (mbox->executor.pid)		// TODO: // not sure if this is correct here
	// {
	// 	free( mbox->executor.pid);
	// 	mbox->executor.pid = NULL;
	// }
	
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

void    free_executor(t_mbox *mbox)
{
	//TODO: Close FDs
}

// nfs/homes/astein/local/bin:/nfs/homes/astein/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin