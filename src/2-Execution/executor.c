/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/16 19:55:23 by anshovah         ###   ########.fr       */
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
    int cur_pipe[2];
    int prev_pipe[2];

    if (pipe(cur_pipe) == -1)
        exit(EXIT_FAILURE);
    // Setup the io struct with FIRST_CMD
    setup_io(minibox, pipe_node->left, FIRST_CMD);
    minibox->executor.io.cmd_fd[CMD_OUT] = cur_pipe[P_LEFT];
    run_cmd_system(minibox, pipe_node->left);
    /*----------------------------------------*/
    prev_pipe[P_RIGHT] = cur_pipe[P_RIGHT];
    prev_pipe[P_LEFT] = cur_pipe[P_LEFT];
    pipe_node = pipe_node->right;
    while (pipe_node->type == PIPE_NODE) {
        if (pipe(cur_pipe) == -1)
            exit(EXIT_FAILURE);
        // Setup the io struct with MIDDLE_CMD
        setup_io(minibox, pipe_node->left, MIDDLE_CMD);
        minibox->executor.io.cmd_fd[CMD_IN] = prev_pipe[P_RIGHT];
        minibox->executor.io.cmd_fd[CMD_OUT] = cur_pipe[P_LEFT];
        run_cmd_system(minibox, pipe_node->left);
        prev_pipe[P_RIGHT] = cur_pipe[P_RIGHT];
        prev_pipe[P_LEFT] = cur_pipe[P_LEFT];
        pipe_node = pipe_node->right;
    }
    /*----------------------------------------*/
    // Setup the io struct with LAST_CMD
    setup_io(minibox, pipe_node, LAST_CMD);
    minibox->executor.io.cmd_fd[CMD_IN] = prev_pipe[P_RIGHT];
    run_cmd_system(minibox, pipe_node);
}

void    execute_cmd(t_minibox *minibox, t_tree *cmd_node, int status)
{
    int builtin_index;
    
    builtin_index = check_if_builtin(minibox, cmd_node->content);
    if (builtin_index != -1)
        run_cmd_builtin(minibox, cmd_node, builtin_index);
    else
    {
        setup_io(minibox, cmd_node, status);
        run_cmd_system(minibox, cmd_node);
    }
}

void    wait_for_execution(t_minibox *minibox)
{
    int pid;
    
    while (true)
    {
        pid = waitpid(-1, &minibox->executor.exit_status, 0);
        if (pid <= 0)
            return ;
        // if (pid == minibox->executor.pid)
    }
}

void    execute(t_minibox *minibox) //TODO: do exit for builtins
{   
    if (minibox->root->type == CMD_NODE)
        execute_cmd(minibox, minibox->root, SINGLE_CMD);
    else
        exec_pipe(minibox, minibox->root);
    wait_for_execution(minibox);   
}
