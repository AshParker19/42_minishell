/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:39 by astein            #+#    #+#             */
/*   Updated: 2023/10/17 20:35:14 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void load_executor(t_minibox *minibox)
{
	char	*path;

	path = get_var_value(minibox, "PATH");
	minibox->executor.path_dirs = ft_split(path, ':');
	initialize_builtins(minibox);
	minibox->executor.cmd_av = NULL;
	minibox->executor.io.prev_pipe[P_LEFT] = -1;
	minibox->executor.io.prev_pipe[P_RIGHT] = -1;
}

int		cmd_counter(t_tree *tree_node)
{
	if(!tree_node)
		return (0);
	if (tree_node->type == CMD_NODE)
		return (1);
	return (1 + cmd_counter(tree_node->right));	
}

void	initialize_io(t_minibox *minibox)
{	
	// minibox->executor.io.redir = redir_node;
	minibox->executor.io.cmd_fd[CMD_IN] = -1;
	minibox->executor.io.cmd_fd[CMD_OUT] = -1;
	minibox->executor.io.dup_fd[CMD_IN] = -1;
	minibox->executor.io.dup_fd[CMD_OUT] = -1;
}

void	free_process(t_minibox *minibox)
{
	// TODO: DOUBLE CHECK IF RIGHT
	if (minibox->executor.cmd_av)
		free_whatever("m", minibox->executor.cmd_av);
	// if (minibox->executor.io.redir)
	// 	free (minibox->executor.io.redir);
	if (minibox->executor.io.cmd_fd[CMD_IN] != -1)
		close (minibox->executor.io.cmd_fd[CMD_IN]);	
	if (minibox->executor.io.cmd_fd[CMD_OUT] != -1)
		close (minibox->executor.io.cmd_fd[CMD_OUT]);
	if (minibox->executor.io.dup_fd[CMD_IN] != -1)
		close (minibox->executor.io.dup_fd[CMD_IN]);
	if (minibox->executor.io.dup_fd[CMD_OUT] != -1)
		close (minibox->executor.io.dup_fd[CMD_OUT]);
	// if (minibox->executor.io.prev_pipe[P_LEFT] != -1)
	// 	close (minibox->executor.io.prev_pipe[P_LEFT]);
	// if (minibox->executor.io.prev_pipe[P_RIGHT] != -1)
	// 	close (minibox->executor.io.prev_pipe[P_RIGHT]);			 
}



/* Print the ouput of the AST built by the Parser*/
void	print_executor_output(t_minibox *minibox, int i)
{
    (void)minibox;
	if(i == 0)
	{
		printf("\n ------------------------------------ \n");
		printf("|              EXECUTOR              |\n");
		printf("|           cmd count: %d            |\n",cmd_counter(minibox->root));
		printf(" ------------------------------------ \n");	
	}
	else
		printf(" ------------------------------------ \n");
}

void    free_executor(t_minibox *minibox)
{
	free_whatever("mm", minibox->executor.path_dirs,
		minibox->executor.cmd_builtins);
	//TODO: Close FDs
}
