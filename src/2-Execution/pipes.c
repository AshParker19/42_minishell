/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:27 by astein            #+#    #+#             */
/*   Updated: 2023/10/08 17:30:20 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// TODO: make this fucntion modular so I can call it in all the cases
void    single_cmd(t_minibox *minibox, t_tree *cmd_node, char *cmd)
{
	int     pid;
	
	pid = 0;
	//TODO: treat redirection
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
