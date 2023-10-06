/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:41 by astein            #+#    #+#             */
/*   Updated: 2023/10/06 19:41:51 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_builtins(t_minibox *minibox)
{
	char	*cmd;

	cmd = "echo|cd|pwd|export|unset|env|exit";
	minibox->executor.cmd_builtins = ft_split(cmd, '|');
}

int    check_if_builtin(t_minibox *minibox, char *cmd_name)
{
    int i;

    i = 0;
    while (minibox->executor.cmd_builtins[i])
    {
        if (ft_strlen(cmd_name) == ft_strlen(minibox->executor.cmd_builtins[i]))
            if (!ft_strncmp(cmd_name, minibox->executor.cmd_builtins[i],
                ft_strlen(cmd_name)))
                return (i);
        i++;
    }
    return (-1);
}

void    run_builtin(t_tree *cmd_node, int builtin_cmd_index)
{
    char    *args_list;
    char    *temp;

    args_list = NULL; 
    while(cmd_node->right)
    {
        if(cmd_node->right->content)
        {
            temp = ft_strcat_multi(2, args_list, cmd_node->right->content)        ;
            free(args_list);
            args_list = temp;
        }    
        cmd_node = cmd_node->right;
    }
    
    if(builtin_cmd_index == 0)
        bultin_echo(cmd_node->right->content);   


    free(args_list);
}
