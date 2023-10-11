/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:41 by astein            #+#    #+#             */
/*   Updated: 2023/10/09 17:49:35 by anshovah         ###   ########.fr       */
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
        if(ft_strcmp_strict(cmd_name, minibox->executor.cmd_builtins[i]))
        // if (ft_strlen(cmd_name) == ft_strlen(minibox->executor.cmd_builtins[i]))
            // if (!ft_strncmp(cmd_name, minibox->executor.cmd_builtins[i],
                // ft_strlen(cmd_name)))
                return (i);
        i++;
    }
    return (-1);
}

static char *strcat_args(t_tree *cmd_node)
{
    char    *args_list;
    char    *temp;

    args_list = NULL; 
    while(cmd_node->right)
    {
        if(cmd_node->right->content)
        {
            temp = ft_strcat_multi(3, args_list, " ", cmd_node->right->content);
            free(args_list);
            args_list = temp;
        }    
        cmd_node = cmd_node->right;
    }
    return(args_list);
}

static void choose_builtin(t_minibox *minibox, int cmd_index,  char *args)
{
    if(cmd_index == 0)
        builtin_echo(args);
    else if(cmd_index == 1)
        builtin_cd(minibox, args);
    else if(cmd_index == 2)
        builtin_pwd(args);
    else if(cmd_index == 3)
        builtin_export(minibox, args);
    else if(cmd_index == 4)
        builtin_unset(minibox, args);
    else if(cmd_index == 5)
        builtin_env(minibox, args);
    else if(cmd_index == 6)
        builtin_exit(minibox, args);
}

void    run_cmd_builtin(t_minibox *minibox, t_tree *cmd_node, int cmd_index)
{
    char    *args_list;
    
    args_list = strcat_args(cmd_node);
    choose_builtin(minibox, cmd_index, args_list);
    free(args_list);
}
