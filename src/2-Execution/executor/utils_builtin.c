/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:41 by astein            #+#    #+#             */
/*   Updated: 2023/10/28 19:24:39 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   initialize the array of 't_builtin_cmd' aka function pointers and
 *          function name
 * 
 *          NOTE: only called once by 'main' on startup
 * 
 * @param mbox 
 */
void	initialize_builtins(t_mbox *mbox)
{
    mbox->executor.builtins[0].cmd_name = "echo";
    mbox->executor.builtins[0].func_name = builtin_echo;
    mbox->executor.builtins[1].cmd_name = "cd";
    mbox->executor.builtins[1].func_name = builtin_cd;
    mbox->executor.builtins[2].cmd_name = "pwd";
    mbox->executor.builtins[2].func_name = builtin_pwd;
    mbox->executor.builtins[3].cmd_name = "export";
    mbox->executor.builtins[3].func_name = builtin_export;
    mbox->executor.builtins[4].cmd_name = "unset";
    mbox->executor.builtins[4].func_name = builtin_unset;
    mbox->executor.builtins[5].cmd_name = "env";
    mbox->executor.builtins[5].func_name = builtin_env;
    mbox->executor.builtins[6].cmd_name = "exit";
    mbox->executor.builtins[6].func_name = builtin_exit;
    mbox->executor.builtins[7].cmd_name = NULL;
    mbox->executor.builtins[7].func_name = NULL;
}

t_bool  is_cmd_builtin(t_mbox *mbox, char *cmd)
{
    int i;
    
    i = -1;
    while (mbox->executor.builtins[++i].cmd_name)
        if (str_cmp_strct(mbox->executor.builtins[i].cmd_name, cmd))
            return (ft_true);
    return (ft_false);
}

void    run_cmd_builtin(t_mbox *mbox, t_ast *cmd_node)
{
    int i;
    
    i = -1;
    while (mbox->executor.builtins[++i].cmd_name)
        if (str_cmp_strct(mbox->executor.builtins[i].cmd_name,
            cmd_node->content))
            mbox->executor.builtins[i].func_name(mbox, cmd_node->right);
}
