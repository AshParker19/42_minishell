/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:41 by astein            #+#    #+#             */
/*   Updated: 2023/10/20 12:42:13 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_builtins(t_minibox *minibox)
{
    minibox->executor.builtins[0].cmd_name = "echo";
    minibox->executor.builtins[0].func_name = builtin_echo;
    minibox->executor.builtins[1].cmd_name = "cd";
    minibox->executor.builtins[1].func_name = builtin_cd;
    minibox->executor.builtins[2].cmd_name = "pwd";
    minibox->executor.builtins[2].func_name = builtin_pwd;
    minibox->executor.builtins[3].cmd_name = "export";
    minibox->executor.builtins[3].func_name = builtin_export;
    minibox->executor.builtins[4].cmd_name = "unset";
    minibox->executor.builtins[4].func_name = builtin_unset;
    minibox->executor.builtins[5].cmd_name = "env";
    minibox->executor.builtins[5].func_name = builtin_env;
    minibox->executor.builtins[6].cmd_name = "exit";
    minibox->executor.builtins[6].func_name = builtin_exit;
    minibox->executor.builtins[7].cmd_name = NULL;
    minibox->executor.builtins[7].func_name = NULL;
}

t_bool  is_cmd_builtin(t_minibox *minibox, char *cmd)
{
    int i;
    
    i = -1;
    while (minibox->executor.builtins[++i].cmd_name)
        if (ft_strcmp_strict(minibox->executor.builtins[i].cmd_name, cmd))
            return (ft_true);
    return (ft_false);
}

// char *strcat_args(t_tree *arg_node)
// {
//     char    *args_list;
//     char    *temp;

//     args_list = NULL; 
//     while(arg_node)
//     {
//         if(arg_node->content)
//         {
//             if(!args_list)
//                 temp = ft_strdup(arg_node->content);
//             else
//                 temp = ft_strcat_multi(3, args_list, " ", arg_node->content);
//             free(args_list);
//             args_list = temp;
//         }    
//         arg_node = arg_node->right;
//     }
//     return(args_list);
// }

void    run_cmd_builtin(t_minibox *minibox, t_tree *cmd_node)
{
    int i;
    
    i = -1;
    while (minibox->executor.builtins[++i].cmd_name)
        if (ft_strcmp_strict(minibox->executor.builtins[i].cmd_name,
            cmd_node->content))
            minibox->executor.builtins[i].func_name(minibox, cmd_node->right);
}
