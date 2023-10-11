/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/11 14:55:31 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    run_cmd_main(t_minibox *minibox, t_tree *cmd_node, int status)
{
    int builtin_cmd_index;
    (void)status;
    
    builtin_cmd_index = check_if_builtin(minibox, cmd_node->content); //TODO: doesn't make sence to have it at 2 places
    if (builtin_cmd_index != -1)
        run_cmd_builtin(minibox, cmd_node, builtin_cmd_index);
    else
        run_cmd_system(minibox, cmd_node);
}

void    setup_io(t_minibox *minibox, int status)
{
    // initialize_io(minibox);
    setup_use_pipe(minibox, status);
    minibox->executor.io.redir = minibox->root->left;//TODO: should be cmd_node??
}

void    run_pipe_main(t_minibox *minibox, t_tree *cmd_node)
{
    if (!cmd_node)
        return ;
    initialize_io(minibox);  //set all the fds as -1 and open a pipe afterwards
    if (pipe(minibox->executor.io.fd) < 0)
    {
        perror("pipe");
        return ; // TODO: exit from here somehow
    }
    minibox->executor.pid1 = fork(); //TODO:error check for forks
    if (minibox->executor.pid1 == 0)
    {
        close (minibox->executor.io.fd[READ_END]);
        minibox->executor.io.dup_fd[WRITE_END]
            = dup2(minibox->executor.io.fd[WRITE_END], STDOUT_FILENO);
        close (minibox->executor.io.fd[WRITE_END]);
        run_cmd_system(minibox, cmd_node->left);
    }
    minibox->executor.pid2 = fork();
    if (minibox->executor.pid2 == 0)
    {
        close (minibox->executor.io.fd[WRITE_END]);
        minibox->executor.io.dup_fd[READ_END]
            = dup2(minibox->executor.io.fd[READ_END], STDIN_FILENO);
        minibox->executor.io.prev_fd = minibox->executor.io.fd[READ_END];  // TODO: store this cunt and reat from it in the next pipe
        close (minibox->executor.io.fd[READ_END]);
        run_cmd_system(minibox, cmd_node->right);
    }
    close (minibox->executor.io.fd[READ_END]);
    close (minibox->executor.io.fd[WRITE_END]);
    waitpid(minibox->executor.pid1, &minibox->executor.exit_status, 0);
    waitpid(minibox->executor.pid2, &minibox->executor.exit_status, 0);
}

static void setup_cmd(t_minibox *minibox, t_tree *tree_node, int status)
{
    int builtin_cmd_index;

    // check if only single buiiltin
    builtin_cmd_index = check_if_builtin(minibox, tree_node->content);
    if (status == SINGLE_CMD && builtin_cmd_index != -1)
        run_cmd_builtin(minibox, tree_node, builtin_cmd_index); //TODO: exit? status redirs?
    else if (status == SINGLE_CMD)
    {
        minibox->executor.pid1 = fork(); //TODO: check for error
        if (minibox->executor.pid1 == 0)
        {
            setup_io(minibox, status);
            setup_redir(minibox);
            run_cmd_main(minibox, tree_node, status);
        }
        waitpid(minibox->executor.pid1, &minibox->executor.exit_status, 0); 
    }    
    else // cases with pipes
    {
        run_pipe_main(minibox, tree_node);
    }
}

void    execute(t_minibox *minibox)
{
    // t_tree  *cur_node;
    
    if (minibox->root->type == CMD_NODE)
        setup_cmd(minibox, minibox->root, SINGLE_CMD);
    else
    {
        run_pipe_main(minibox, minibox->root);
        // setup_cmd(minibox, minibox->root->left, FIRST_CMD);
        // cur_node = minibox->root;
        // while(cur_node->right && (cur_node->right->type == PIPE_NODE))
        // {
        //     printf("NOT HERE\n");
        //     setup_cmd(minibox, cur_node->left, MIDDLE_CMD);
        //     cur_node = cur_node->right;
        // }
        // setup_cmd(minibox, cur_node->right,  LAST_CMD);
    }
}
