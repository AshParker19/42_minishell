/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:39 by astein            #+#    #+#             */
/*   Updated: 2023/10/11 11:29:18 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void load_executor(t_minibox *minibox)
{
	char	*path;

	path = get_var(minibox, "PATH");
	minibox->executor.path_dirs = ft_split(path, ':');
	initialize_builtins(minibox);
	minibox->executor.cmd_av = NULL;
}

void	initialize_io(t_minibox *minibox)
{	
	minibox->executor.io.fd[READ_END] = -1;
	minibox->executor.io.fd[WRITE_END] = -1;
	minibox->executor.io.dup_fd[READ_END] = -1;
	minibox->executor.io.dup_fd[WRITE_END] = -1;
	minibox->executor.io.prev_fd = -1;
}

void	free_process(t_minibox *minibox)
{
	// TODO: DOUBLE CHECK IF RIGHT
	if (minibox->executor.cmd_av)
		free_matrix(minibox->executor.cmd_av, -1);
	if (minibox->executor.io.fd[READ_END] != -1)
		close (minibox->executor.io.fd[READ_END]);
	if (minibox->executor.io.fd[WRITE_END] != -1)
		close (minibox->executor.io.fd[WRITE_END]);
	if (minibox->executor.io.dup_fd[READ_END] != -1)
		close (minibox->executor.io.dup_fd[READ_END]);
	if (minibox->executor.io.dup_fd[WRITE_END] != -1)
		close (minibox->executor.io.dup_fd[WRITE_END]);			 
}



/* Print the ouput of the AST built by the Parser*/
void	print_executor_output(t_minibox *minibox, int i)
{
    (void)minibox;
	if(i == 0)
	{
		printf("\n ------------------------------------ \n");
		printf("|              EXECUTOR              |\n");
		printf(" ------------------------------------ \n");	
	}
	else
		printf(" ------------------------------------ \n");
}

void    free_executor(t_minibox *minibox)
{
	free_matrix(minibox->executor.path_dirs, -1);
	free_matrix(minibox->executor.cmd_builtins, -1);
	//TODO: Close FDs
}
