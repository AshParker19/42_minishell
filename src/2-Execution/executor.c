/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/20 16:28:38 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	decides if the command to be executed is a builtin cmd or a system cmd
*/
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
/*
	
*/
static void single_cmd(t_minibox *minibox)
{
	minibox->executor.io.cmd_fd[CMD_IN] = STDIN_FILENO;
	minibox->executor.io.cmd_fd[CMD_OUT] = STDOUT_FILENO;
	setup_redir(minibox, minibox->root->left);
	run_cmd_builtin(minibox, minibox->root);  
	if (minibox->executor.io.cmd_fd[CMD_IN] != STDIN_FILENO)
		close (minibox->executor.io.cmd_fd[CMD_IN]);
	if (minibox->executor.io.cmd_fd[CMD_OUT] != STDOUT_FILENO)
		close (minibox->executor.io.cmd_fd[CMD_OUT]);  
	minibox->executor.io.cmd_fd[CMD_IN] = -1;
	minibox->executor.io.cmd_fd[CMD_OUT] = -1;
	free_process(minibox);
}

static void perform_child(t_minibox *minibox, t_tree *cmd_node, int cmd_pos, int *cur_pipe)
{
	// dprintf(2, "CHILD(%s) \tPID(%d)\n", cmd_node->content, getpid());
	// if (cmd_pos == LAST_CMD && is_cmd_builtin(minibox, cmd_node->content))
	if (is_cmd_builtin(minibox, cmd_node->content))
	{
		minibox->executor.io.cmd_fd[CMD_IN] = STDIN_FILENO;
		minibox->executor.io.cmd_fd[CMD_OUT] = STDOUT_FILENO;
	}
	setup_pipes(minibox, cur_pipe);
	setup_redir(minibox, cmd_node->left);
	setup_process_std(minibox);
	if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		close(cur_pipe[P_RIGHT]);
	if (cmd_pos != FIRST_CMD && minibox->executor.io.prev_pipe[P_RIGHT] != -1)
		close(minibox->executor.io.prev_pipe[P_RIGHT]);
	run_cmd_main(minibox, cmd_node);
}

static void	perform_parent(t_minibox *minibox, t_tree *cmd_node, int cmd_pos, int *cur_pipe)
{
	if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		close(cur_pipe[P_LEFT]);
	if (cmd_pos != FIRST_CMD && cmd_pos != SINGLE_CMD)
		close(minibox->executor.io.prev_pipe[P_RIGHT]);
	minibox->executor.pid_index++;
	minibox->executor.io.prev_pipe[P_RIGHT] = cur_pipe[P_RIGHT];
	minibox->executor.io.prev_pipe[P_LEFT] = cur_pipe[P_LEFT];
	free_process(minibox);	
}

void    execute_cmd(t_minibox *minibox, t_tree *cmd_node, int cmd_pos)
{
	int cur_pipe[2];

	initialize_io(minibox);
	// TODO: if cmd_node = ./minishell increment shell level
	// FIXME: if we change minishell to frankenshell we have to change it here as well
	// checks if we do NOT have a single builtin cmd -> then fork!
	if (cmd_pos == SINGLE_CMD && is_cmd_builtin(minibox, cmd_node->content))
		single_cmd(minibox);
	else
	{
		setup_use_pipe(minibox, cmd_pos);
		if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		{
			if (pipe(cur_pipe) == -1)
				exit(EXIT_FAILURE); //TODO:
		}
		//listen_to_signals = ft_true;
		minibox->executor.pid[minibox->executor.pid_index] = fork(); //TODO: check for builtins!
		if (minibox->executor.pid[minibox->executor.pid_index] == -1)
			exit(EXIT_FAILURE); //TODO:    
		if (minibox->executor.pid[minibox->executor.pid_index] == 0)
			perform_child(minibox, cmd_node, cmd_pos, cur_pipe);
		else
			perform_parent(minibox, cmd_node, cmd_pos, cur_pipe);
	}
}

void    wait_for_execution(t_minibox *minibox)
{
	int i;
	
	i = -1;
	while (++i < cmd_counter(minibox->root))
		waitpid(minibox->executor.pid[i], &minibox->executor.exit_status, 0);
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
