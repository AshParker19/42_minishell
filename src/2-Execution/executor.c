/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/13 11:04:26 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void    run_cmd_main(t_minibox *minibox, t_tree *cmd_node, int status)
// {
//     int builtin_cmd_index;
//     (void)status;
    
//     builtin_cmd_index = check_if_builtin(minibox, cmd_node->content); //TODO: doesn't make sence to have it at 2 places
//     if (builtin_cmd_index != -1)
//         run_cmd_builtin(minibox, cmd_node, builtin_cmd_index);
//     else
//         run_cmd_system(minibox, cmd_node);
// }

void    setup_io(t_minibox *minibox, t_tree *cmd_node, int status)
{
    initialize_io(minibox);
    setup_use_pipe(minibox, status);
    minibox->executor.io.redir = cmd_node->left;
}

void    exec_pipe(t_minibox *minibox, t_tree *pipe_node)
{
    int pipe_fd[2];
    int prev_pipe[2];

    if (pipe(pipe_fd) == -1)
        exit(EXIT_FAILURE);
    // Setup the io struct with FIRST_CMD
    setup_io(minibox, pipe_node->left, FIRST_CMD);
    minibox->executor.io.fd[1] = pipe_fd[1];
    run_cmd_system(minibox, pipe_node->left);
    prev_pipe[0] = pipe_fd[0];
    prev_pipe[1] = pipe_fd[1];
    pipe_node = pipe_node->right;
    while (pipe_node->type == PIPE_NODE) {
        if (pipe(pipe_fd) == -1)
            exit(EXIT_FAILURE);
        // Setup the io struct with MIDDLE_CMD
        setup_io(minibox, pipe_node->left, MIDDLE_CMD);
        minibox->executor.io.fd[0] = prev_pipe[0];
        minibox->executor.io.fd[1] = pipe_fd[1];
        run_cmd_system(minibox, pipe_node->left);
        prev_pipe[0] = pipe_fd[0];
        prev_pipe[1] = pipe_fd[1];
        pipe_node = pipe_node->right;
    }
    // Setup the io struct with LAST_CMD
    setup_io(minibox, pipe_node, LAST_CMD);
    minibox->executor.io.fd[0] = prev_pipe[0];
    run_cmd_system(minibox, pipe_node);
}

// static void setup_cmd(t_minibox *minibox, t_tree *tree_node, int status)
// {
//     int builtin_cmd_index;

//     // check if only single buiiltin
//     builtin_cmd_index = check_if_builtin(minibox, tree_node->content);
//     if (status == SINGLE_CMD && builtin_cmd_index != -1)
//         run_cmd_builtin(minibox, tree_node, builtin_cmd_index); //TODO: exit? status redirs?
//     else if (status == SINGLE_CMD)
//     {
//         minibox->executor.pid1 = fork(); //TODO: check for error
//         if (minibox->executor.pid1 == 0)
//         {
//             setup_io(minibox, status);
//             setup_redir(minibox);
//             run_cmd_main(minibox, tree_node, status);
//         }
//         waitpid(minibox->executor.pid1, &minibox->executor.exit_status, 0); 
//     }    
//     else // cases with pipes
//     {
//         run_pipe_main(minibox, tree_node);
//     }
// }

void    execute_cmd(t_minibox *minibox, t_tree *tree_node, int status)
{
    // Setup IO
    setup_io(minibox, tree_node, status);
    // Execute cmd
    run_cmd_system(minibox, tree_node);
    // Free anything if necessary
}

void    execute(t_minibox *minibox)
{
    if (minibox->root->type == CMD_NODE)
        execute_cmd(minibox, minibox->root, SINGLE_CMD);
    else
        exec_pipe(minibox, minibox->root);
}
