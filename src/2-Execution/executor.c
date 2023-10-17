/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/17 20:44:15 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    run_cmd_main(t_minibox *minibox, t_tree *cmd_node)
{
    int builtin_index;
    
    builtin_index = check_if_builtin(minibox, cmd_node->content);
    if (builtin_index != -1)
    {
        run_cmd_builtin(minibox, cmd_node, builtin_index);
        exit (0); //TODO: make exit status
    }
    else
        run_cmd_system(minibox, cmd_node);
}

// void    execute_cmd(t_minibox *minibox, t_tree *cmd_node, int status)
// {
//     int builtin_index;
    
//     builtin_index = check_if_builtin(minibox, cmd_node->content);
//     if (builtin_index != -1)
//         run_cmd_builtin(minibox, cmd_node, builtin_index);
//     else
//     {
//         setup_io(minibox, cmd_node, status);
//         run_cmd_system(minibox, cmd_node);
//     }
// }



void    execute_cmd(t_minibox *minibox, t_tree *cmd_node, int cmd_position)
{
    int cur_pipe[2];

    // preparing the preparing
    initialize_io(minibox);
    setup_use_pipe(minibox, cmd_position);
    
    // pipe
    if (cmd_position == FIRST_CMD || cmd_position == MIDDLE_CMD)
    {
        if (pipe(cur_pipe) == -1)
            exit(EXIT_FAILURE); //TODO:
    }
    if (minibox->executor.io.use_pipe[CMD_IN])
        minibox->executor.io.cmd_fd[CMD_IN]
            = minibox->executor.io.prev_pipe[P_RIGHT];
    if (minibox->executor.io.use_pipe[CMD_OUT])
        minibox->executor.io.cmd_fd[CMD_OUT] = cur_pipe[P_LEFT];
    
    // fork
    /*******************************************/
    minibox->executor.pid = fork(); //TODO: check for builtins!
    if (minibox->executor.pid == -1)
        exit(EXIT_FAILURE); //TODO:
    if (minibox->executor.pid == 0)
    {
        setup_pipes(minibox);
    // redir
        setup_redir(minibox, cmd_node->left);
        run_cmd_main(minibox, cmd_node);
    }   
    /*******************************************/
    minibox->executor.io.prev_pipe[P_RIGHT] = cur_pipe[P_RIGHT];
    minibox->executor.io.prev_pipe[P_LEFT] = cur_pipe[P_LEFT];
    free_process(minibox);
    
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

/**
 * This function traverses trough the AST
 * checks cmd POSITION
 * 
 *      SINGLE          ls -l
 * 
 *              FIRST       MIDDLE          LAST
 *      input:  ls -l   | grep "Makefile" | wc
 * 
 *  then calls execute_cmd and waits until all childs died
*/
void    execute(t_minibox *minibox) //TODO: do exit for builtins
{   
    t_tree  *current;
    
    current = minibox->root;
    // TODO: need this somewhere i guess cmd_counter()
    
    if (current->type == CMD_NODE)
        execute_cmd(minibox, current, SINGLE_CMD);
    else
    {
        execute_cmd(minibox, current->left, FIRST_CMD);
        while (current->right->type == PIPE_NODE)
        {
            current = current->right;
            execute_cmd(minibox, current->left, MIDDLE_CMD);
        }
        execute_cmd(minibox, current->right, LAST_CMD);   
    }
    wait_for_execution(minibox);   
}
