/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/23 15:02:49 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char    *get_cmd_path(t_minibox *minibox, char *cmd, int i)
{
    int     check;
    char    *path;
    
    if (ft_strchr(cmd, '/'))
    {
        check = access(cmd, F_OK);
        if (!check)
            return (ft_strdup(cmd));
        return (NULL);    
    }
    while (minibox->executor.path_dirs[++i])
    {
        path = ft_strcat_multi(3, minibox->executor.path_dirs[i], "/", cmd);
        check = access(path, F_OK);
        if (!check)
            return (path);
        else
            free (path);    
    }
    return (NULL);
}

void get_cmd_av(t_minibox *minibox, t_tree *cmd_node)
{
    char    *cur_args_str;
    char    *temp;
    
    if (!cmd_node && !cmd_node->content) //TODO: not sure if it need a content
        return ;
    cur_args_str = get_cmd_path(minibox, cmd_node->content, -1);
    if (!cur_args_str)
        return ;
    while (cmd_node->right)
    {
        if (cmd_node->right->content)
        {
            temp = ft_strcat_multi(3, cur_args_str, "|", cmd_node->right->content);
            free (cur_args_str);
            cur_args_str = temp;
        }
        cmd_node = cmd_node->right;
    }
    minibox->executor.cmd_av = ft_split(cur_args_str, '|');
    free(cur_args_str);
}

void    run_cmd_system(t_minibox *minibox, t_tree *cmd_node)
{
    char       *error_msg;
    
        if (minibox->executor.io.cmd_fd[CMD_IN] != -1)
            close(minibox->executor.io.cmd_fd[CMD_IN]);
        if (minibox->executor.io.cmd_fd[CMD_OUT] != -1)
            close(minibox->executor.io.cmd_fd[CMD_OUT]);
        get_cmd_av(minibox, cmd_node);
        if(minibox->executor.cmd_av)
            execve(minibox->executor.cmd_av[0], minibox->executor.cmd_av, env_to_matrix(minibox));
        if (ft_strrchr(cmd_node->content, '/'))    
            create_error_msg("nnn", "command '", ft_strrchr(cmd_node->content, '/'), "' not found");
        else
            create_error_msg("nnn", "command '", cmd_node->content, "' not found");
        free_process(minibox);
        exit(127);
        // TODO: EXIT 
}

