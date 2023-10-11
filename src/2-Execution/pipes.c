/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:27 by astein            #+#    #+#             */
/*   Updated: 2023/10/10 17:24:36 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_use_pipe(t_minibox *minibox, int status)
{
    if (status == FIRST_CMD)
    {
        minibox->executor.io.use_pipe[READ_END] = ft_false;
        minibox->executor.io.use_pipe[WRITE_END] = ft_true;
    }
    else if (status == MIDDLE_CMD)
    {
        minibox->executor.io.use_pipe[READ_END] = ft_true;
        minibox->executor.io.use_pipe[WRITE_END] = ft_true;
    }
    else if (status == LAST_CMD)
    {
        minibox->executor.io.use_pipe[READ_END] = ft_true;
        minibox->executor.io.use_pipe[WRITE_END] = ft_false;
    }
}

// // TODO: make this fucntion modular so I can call it in all the cases
// void    single_cmd(t_minibox *minibox, t_tree *cmd_node, char *cmd)
// {
// 	int     pid;
	
// 	pid = 0;
// 	//TODO: treat redirection
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror ("fork");
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		get_cmd_av(minibox, cmd_node);
// 		execve(cmd, minibox->executor.cmd_av, minibox->env);
// 		perror ("execve");
// 		free_process(minibox);
// 		free (cmd);
// 	}
// }
