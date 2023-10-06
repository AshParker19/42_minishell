/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:23:39 by astein            #+#    #+#             */
/*   Updated: 2023/10/06 19:35:27 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void load_executor(t_minibox *minibox)
{
	char	*path;

	path = get_var(minibox, "PATH");
	minibox->executor.path_dirs = ft_split(path, ':');
	initialize_builtins(minibox);
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