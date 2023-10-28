/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/10/28 14:37:23 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	decides if the command to be executed is a builtin cmd or a system cmd
*/
static void    run_cmd_main(t_mbox *mbox, t_tree *cmd_node)
{
	if (is_cmd_builtin(mbox, cmd_node->content))
	{
		run_cmd_builtin(mbox, cmd_node);
		free_process(mbox);
		exit (0); //TODO: make exit status
	}
	else
	{
		run_cmd_system(mbox, cmd_node);
		free_process(mbox);	
	}
}
/*
	
*/
static t_bool single_cmd(t_mbox *mbox)
{
	mbox->executor.io.cmd_fd[CMD_IN] = STDIN_FILENO;
	mbox->executor.io.cmd_fd[CMD_OUT] = STDOUT_FILENO;
	if (!setup_redir(mbox, mbox->root->left))
	{
		if (mbox->executor.io.cmd_fd[CMD_IN] != STDIN_FILENO)
			close (mbox->executor.io.cmd_fd[CMD_IN]);
		if (mbox->executor.io.cmd_fd[CMD_OUT] != STDOUT_FILENO)
			close (mbox->executor.io.cmd_fd[CMD_OUT]);  
		mbox->executor.io.cmd_fd[CMD_IN] = -1;
		mbox->executor.io.cmd_fd[CMD_OUT] = -1;
		return (ft_false);
	}
	run_cmd_builtin(mbox, mbox->root);  
	if (mbox->executor.io.cmd_fd[CMD_IN] != STDIN_FILENO)
		close (mbox->executor.io.cmd_fd[CMD_IN]);
	if (mbox->executor.io.cmd_fd[CMD_OUT] != STDOUT_FILENO)
		close (mbox->executor.io.cmd_fd[CMD_OUT]);  
	mbox->executor.io.cmd_fd[CMD_IN] = -1;
	mbox->executor.io.cmd_fd[CMD_OUT] = -1;
	free_process(mbox);
	return (ft_true);
}

static void perform_child(t_mbox *mbox, t_tree *cmd_node, int cmd_pos, int *cur_pipe)
{
	if (cmd_pos == SINGLE_CMD && ft_strcmp_strict("./minishell", cmd_node->content))
		increment_shlvl(mbox);	
	if (is_cmd_builtin(mbox, cmd_node->content))
	{
		mbox->executor.io.cmd_fd[CMD_IN] = STDIN_FILENO;
		mbox->executor.io.cmd_fd[CMD_OUT] = STDOUT_FILENO;
	}
	setup_pipes(mbox, cur_pipe);
	if (!setup_redir(mbox, cmd_node->left))
		free_and_close_box(mbox);
	setup_process_std(mbox);
	if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		close(cur_pipe[P_RIGHT]);
	if (cmd_pos != FIRST_CMD && mbox->executor.io.prev_pipe[P_RIGHT] != -1)
		close(mbox->executor.io.prev_pipe[P_RIGHT]);
	run_cmd_main(mbox, cmd_node);
	free_and_close_box(mbox);
}

static void	perform_parent(t_mbox *mbox, t_tree *cmd_node, int cmd_pos, int *cur_pipe)
{
	if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		close(cur_pipe[P_LEFT]);
	if (cmd_pos != FIRST_CMD && cmd_pos != SINGLE_CMD)
		close(mbox->executor.io.prev_pipe[P_RIGHT]);
	mbox->executor.pid_index++;
	mbox->executor.io.prev_pipe[P_RIGHT] = cur_pipe[P_RIGHT];
	mbox->executor.io.prev_pipe[P_LEFT] = cur_pipe[P_LEFT];
	free_process(mbox);	
}

t_bool    execute_cmd(t_mbox *mbox, t_tree *cmd_node, int cmd_pos)
{
	int cur_pipe[2];

	initialize_io(mbox);
	// TODO: if cmd_node = ./minishell increment shell level
	// FIXME: if we change minishell to frankenshell we have to change it here as well
	// checks if we do NOT have a single builtin cmd -> then fork!
	if (cmd_pos == SINGLE_CMD && is_cmd_builtin(mbox, cmd_node->content))
		return (single_cmd(mbox));
	else
	{
		setup_use_pipe(mbox, cmd_pos);
		if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		{
			if (pipe(cur_pipe) == -1)
				exit(EXIT_FAILURE); //TODO:
		}
		//listen_to_signals = ft_true;
		mbox->executor.pid[mbox->executor.pid_index] = fork(); //TODO: check for builtins!
		if (mbox->executor.pid[mbox->executor.pid_index] == -1)
			exit(EXIT_FAILURE); //TODO:    
		if (mbox->executor.pid[mbox->executor.pid_index] == 0)
			perform_child(mbox, cmd_node, cmd_pos, cur_pipe);
		else
			perform_parent(mbox, cmd_node, cmd_pos, cur_pipe);
	}
	return (ft_true);
}

void    wait_for_execution(t_mbox *mbox)
{
	int i;
	int	exit_status;
	
	i = -1;
	while (++i < cmd_counter(mbox->root))
	{
		waitpid(mbox->executor.pid[i], &exit_status, 0);
		set_var_value(mbox, "?", ft_itoa(exit_status));		
	}
	if (WIFEXITED(exit_status))
		set_var_value(mbox, "?", ft_itoa(WEXITSTATUS(exit_status)));
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
t_bool    execute(t_mbox *mbox) //TODO: do exit for builtins
{   
	t_tree  *cur;
	
	reset_executor(mbox);
	mbox->executor.pid = ft_calloc(cmd_counter(mbox->root), sizeof(int));
	if (!mbox->executor.pid)
		return (ft_false);
	cur = mbox->root;
	if (cur->type == CMD_NODE)
	{
		if (!execute_cmd(mbox, cur, SINGLE_CMD))
			return (ft_false);
	}
	else
	{
		execute_cmd(mbox, cur->left, FIRST_CMD);
		while (cur->right->type == PIPE_NODE)
		{
			cur = cur->right;
			execute_cmd(mbox, cur->left, MIDDLE_CMD);
		}
		execute_cmd(mbox, cur->right, LAST_CMD);   
	}
	wait_for_execution(mbox);
	return (ft_true);
}


