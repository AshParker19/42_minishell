/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:41 by astein            #+#    #+#             */
/*   Updated: 2023/10/13 23:04:21 by astein           ###   ########.fr       */
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

char *strcat_args(t_tree *arg_node)
{
    char    *args_list;
    char    *temp;

    args_list = NULL; 
    while(arg_node)
    {
        if(arg_node->content)
        {
            if(!args_list)
                temp = ft_strdup(arg_node->content);
            else
                temp = ft_strcat_multi(3, args_list, " ", arg_node->content);
            free(args_list);
            args_list = temp;
        }    
        arg_node = arg_node->right;
    }
    return(args_list);
}

void    run_cmd_builtin(t_minibox *minibox, t_tree *cmd_node, int cmd_index)
{
    void	(*f[7])(t_minibox *minibox, t_tree *arg_node);
    
    if(cmd_index < 0 || cmd_index > 6)
        return ; // TODO: exit print message
    f[0] = builtin_echo;
    f[1] = builtin_cd;
	f[2] = builtin_pwd;
	f[3] = builtin_export;
	f[4] = builtin_unset;
	f[5] = builtin_env;
	f[6] = builtin_exit;
    (*f[cmd_index])(minibox, cmd_node->right);
}
