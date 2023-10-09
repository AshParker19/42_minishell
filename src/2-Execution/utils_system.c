/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/09 20:54:11 by anshovah         ###   ########.fr       */
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
    get_cmd_av(minibox, cmd_node);
    printf("%s\n",minibox->executor.cmd_av[0]);
    int i = 0;
    printf ("============\n");
    while (minibox->executor.cmd_av[i])
    {
        printf ("%s\n", minibox->executor.cmd_av[i]);
        i++;
    }
    if(!minibox->executor.cmd_av)
        execve("ls\0", minibox->executor.cmd_av, minibox->env);
    perror ("execve");
    free_process(minibox);     
}

// void get_cmd_av(t_minibox *minibox, t_tree *root)
// {
//     int i = 0;
//     for (t_tree *it = root; it; it = it->right, i++);
//     minibox->executor.cmd_av = ft_calloc(i + 1, sizeof(char *));
//     for (int i = 0; root; root = root->right, i++)
//         minibox->executor.cmd_av[i] = ft_strdup(root->content);
// }
