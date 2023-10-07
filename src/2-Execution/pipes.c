/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:27 by astein            #+#    #+#             */
/*   Updated: 2023/10/07 16:40:54 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// TODO: make this fucntion modular so I can call it in all the cases
void    single_cmd(t_minibox *minibox, t_tree *cmd_node, char *cmd)
{
	t_tree	*save;
	int     pid;
	
	save = cmd_node;
	pid = 0;
	// if (cmd_node->left)
	// {
	// 	while (cmd_node->left)
	// 		cmd_node = cmd_node->left;
	// }
	pid = fork();
	if (pid < 0)
	{
		perror ("fork");
		return ;
	}
	if (pid == 0)
	{
		get_cmd_av(minibox, cmd_node);
		execve(cmd, minibox->executor.cmd_av, minibox->env);
		perror ("execve");
		free_process(minibox);
		free (cmd);
	}
}
