/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/08 19:22:22 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    execute_cmd(t_minibox *minibox, t_tree *tree_node)
{
    char    *cmd;
    
    get_cmd_av(minibox, tree_node);
    cmd = find_cmd(minibox, tree_node->content, -1);
    execve(cmd, minibox->executor.cmd_av, minibox->env);
    perror ("execve");
    // free_process(minibox);
    free (cmd);
}

void    execute_pipe(t_minibox *minibox, t_tree *tree_node)
{
    if (!tree_node || tree_node->type != PIPE_NODE)
        return ;
    if (pipe(minibox->executor.fd) < 0)
    {
        perror("pipe");
        return ; // TODO: exit from here somehow
    }
    if (minibox->executor.prev_fd != -1)
        minibox->executor.prev_fd = minibox->executor.fd[WRITE_END];
    minibox->executor.pid1 = fork();
    if (minibox->executor.pid1 < 0)
    {
        perror("fork");
        return ;
    }
    if (minibox->executor.pid1 == 0)
    {
        close (minibox->executor.fd[READ_END]);
        minibox->executor.dup_fd[WRITE_END]    
            = dup2(minibox->executor.fd[WRITE_END], STDOUT_FILENO);
        close (minibox->executor.fd[WRITE_END]);
        execute_cmd(minibox, tree_node->left);
    }
    minibox->executor.pid2 = fork();
    if (minibox->executor.pid2 < 0)
    {
        perror("fork");
        return ;
    }
    if (minibox->executor.pid2 == 0)
    {
        close (minibox->executor.fd[WRITE_END]);
        minibox->executor.dup_fd[READ_END]
            = dup2(minibox->executor.fd[READ_END], STDIN_FILENO);
        close (minibox->executor.fd[READ_END]);
        execute_cmd(minibox, tree_node->right);
    }
    close(minibox->executor.fd[READ_END]);
    close(minibox->executor.fd[WRITE_END]);
    waitpid(minibox->executor.pid1, &minibox->executor.exit_status, 0);
    waitpid(minibox->executor.pid2, &minibox->executor.exit_status, 0);
}

void    execute_recursively(t_minibox *minibox, t_tree *tree_node)
{
    if (!tree_node)
        return ;  
    if (tree_node->type == PIPE_NODE)
        execute_pipe(minibox, tree_node);
    execute_recursively(minibox, tree_node->left);
    execute_recursively(minibox, tree_node->right);
}


void    execute(t_minibox *minibox)
{
    int builtin_cmd_index;
    initialize_executor(minibox);
    
    if(minibox->root->type == CMD_NODE)
    {
        builtin_cmd_index = check_if_builtin(minibox, minibox->root->content);
        if(builtin_cmd_index != -1)
            run_builtin(minibox->root, builtin_cmd_index);
        else
        {
            single_cmd(minibox, minibox->root,
                find_cmd(minibox, minibox->root->content, -1));
            wait(NULL);                 
        }
    }
    else
        execute_recursively(minibox, minibox->root);
    // free_process(minibox);    
}
