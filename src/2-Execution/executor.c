/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/19 21:31:05 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    run_cmd_main(t_minibox *minibox, t_tree *cmd_node)
{
    if (is_cmd_builtin(minibox, cmd_node->content))
    {
        run_cmd_builtin(minibox, cmd_node);
        free_process(minibox);
        exit (0); //TODO: make exit status
    }
    else
    {
        run_cmd_system(minibox, cmd_node);
        free_process(minibox);
    }
}

void    execute_cmd(t_minibox *minibox, t_tree *cmd_node, int cmd_position)
{
    int cur_pipe[2];

    // preparing the preparing
    initialize_io(minibox);
    
    // TODO: if cmd_node = ./minishell increment shell level
    // FIXME: if we change minishell to frankenshell we have to change it here as well
    

    // checks if we do NOT have a single builtin cmd -> then fork!
    if (cmd_position == SINGLE_CMD && is_cmd_builtin(minibox, cmd_node->content))
    {
        minibox->executor.io.cmd_fd[CMD_IN] = STDIN_FILENO;
        minibox->executor.io.cmd_fd[CMD_OUT] = STDOUT_FILENO;
        setup_redir(minibox, cmd_node->left);
        run_cmd_builtin(minibox, cmd_node);  
        if (minibox->executor.io.cmd_fd[CMD_IN] != STDIN_FILENO)
            close (minibox->executor.io.cmd_fd[CMD_IN]);
        if (minibox->executor.io.cmd_fd[CMD_OUT] != STDOUT_FILENO)
            close (minibox->executor.io.cmd_fd[CMD_OUT]);  
        minibox->executor.io.cmd_fd[CMD_IN] = -1;
        minibox->executor.io.cmd_fd[CMD_OUT] = -1;
        free_process(minibox);
        return ;
    }
    // pipe
    setup_use_pipe(minibox, cmd_position);
    if (cmd_position == FIRST_CMD || cmd_position == MIDDLE_CMD)
    {
        if (pipe(cur_pipe) == -1)
            exit(EXIT_FAILURE); //TODO:
    }
    //listen_to_signals = ft_true;
    // FORKING
    minibox->executor.pid[minibox->executor.pid_index] = fork(); //TODO: check for builtins!
    if (minibox->executor.pid[minibox->executor.pid_index] == -1)
        exit(EXIT_FAILURE); //TODO:    
    dbg_printf(no_block, "NOT a single builtin cmd found!! So fork! pid[%d] index [%d]\n", minibox->executor.pid[minibox->executor.pid_index], minibox->executor.pid_index);   
    if (minibox->executor.pid[minibox->executor.pid_index] == 0)
    {
        dbg_printf(no_block, "INSIDE CHILD\n");
        setup_pipes(minibox, cur_pipe);
        setup_redir(minibox, cmd_node->left);
        setup_process_std(minibox);
        if (cmd_position == FIRST_CMD || cmd_position == MIDDLE_CMD)
        {
            close(cur_pipe[P_RIGHT]);
            close(cur_pipe[P_LEFT]);
        }
        if (cmd_position != FIRST_CMD && minibox->executor.io.prev_pipe[P_RIGHT] != -1)
            close(minibox->executor.io.prev_pipe[P_RIGHT]);
        run_cmd_main(minibox, cmd_node);
    }
    else
    {
        dbg_printf(no_block, "INSIDE PARENT\n");
        minibox->executor.pid_index++;
        if (cmd_position == FIRST_CMD || cmd_position == MIDDLE_CMD)
            close(cur_pipe[P_LEFT]);
        if (cmd_position != FIRST_CMD && cmd_position != SINGLE_CMD)
            close(minibox->executor.io.prev_pipe[P_RIGHT]);
    }
    /*******************************************/
    minibox->executor.io.prev_pipe[P_RIGHT] = cur_pipe[P_RIGHT];
    minibox->executor.io.prev_pipe[P_LEFT] = cur_pipe[P_LEFT];
    free_process(minibox);
}

void    wait_for_execution(t_minibox *minibox)
{
    int pid;
    int i;
    
    // while (true)
    // {
    //     pid = waitpid(-1, &minibox->executor.exit_status, 0);
    //     if (pid <= 0)
    //         return ;
    //     // if (pid == minibox->executor.pid)
    // }
    i = -1;
    while (++i < cmd_counter(minibox->root))
    {
        dbg_printf(no_block,  "PID %d\n", minibox->executor.pid[i]);
        waitpid(minibox->executor.pid[i], &minibox->executor.exit_status, 0);
    }
}

/*
 * This function traverses trough the AST
 * checks cmd POSITION
 * 
 *      SINGLE          ls -l
 * 
 *              FIRST       MIDDLE          LAST
 *      input:  ls -l   | grep "Makefile" | wc -l
 * 
 *  then calls execute_cmd and waits until all childs died
*/
void    execute(t_minibox *minibox) //TODO: do exit for builtins
{   
    t_tree  *current;
    
    reset_executor(minibox);
    minibox->executor.pid = ft_calloc(cmd_counter(minibox->root), sizeof(int));
    if (!minibox->executor.pid)
        return ; //TODO: EXIT NICELY
    current = minibox->root;
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
