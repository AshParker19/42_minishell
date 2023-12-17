/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/12/17 18:41:52 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

static void	exec_child(t_mbox *mbox, t_ast *cmd_node, int *cur_p)
{
	if (is_cmd_builtin(mbox, cmd_node->content))
		conf_sig_handler(SIG_STATE_CHILD_BUILTIN);
	else
		conf_sig_handler(SIG_STATE_CHILD);
	setup_pipes(mbox, cur_p);
	if (!configure_redir(mbox, cmd_node->left, cur_p))
	{
		if (cmd_node->cmd_pos == FIRST_CMD || cmd_node->cmd_pos == MIDDLE_CMD)
			close(cur_p[P_RIGHT]);
		if (cmd_node->cmd_pos != FIRST_CMD
			&& mbox->exec.io.prev_pipe[P_RIGHT] != -1)
			close(mbox->exec.io.prev_pipe[P_RIGHT]);
		destroy_mbox(mbox);
	}
	setup_process_std_tmp(mbox);
	if (cmd_node->cmd_pos == FIRST_CMD || cmd_node->cmd_pos == MIDDLE_CMD)
		close(cur_p[P_RIGHT]);
	if (cmd_node->cmd_pos != FIRST_CMD
		&& mbox->exec.io.prev_pipe[P_RIGHT] != -1)
		close(mbox->exec.io.prev_pipe[P_RIGHT]);
	run_cmd_main(mbox, cmd_node);
	destroy_mbox(mbox);
}

static t_bool	exec_parent(t_mbox *mbox, int *cur_p, t_ast *node, int kid_pid)
{
	t_ast	*cmd_node_cpy;

	if (node->cmd_pos == FIRST_CMD || node->cmd_pos == MIDDLE_CMD)
		close(cur_p[P_LEFT]);
	if (node->cmd_pos != FIRST_CMD && node->cmd_pos != SINGLE_CMD)
		close(mbox->exec.io.prev_pipe[P_RIGHT]);
	mbox->exec.pid_index++;
	mbox->exec.io.prev_pipe[P_RIGHT] = cur_p[P_RIGHT];
	mbox->exec.io.prev_pipe[P_LEFT] = cur_p[P_LEFT];
	close_process_fds_v2(mbox);
	cmd_node_cpy = node;
	return (hd_parent_wait(mbox, cur_p, cmd_node_cpy, kid_pid));
}

/**
 * @brief	
 * 
 * @param	mbox 
 * @param	cmd_node 
 * @param	cmd_pos 
 * @return	t_bool 
 */
static t_bool	execute_cmd(t_mbox *mbox, t_ast *cmd_node, int cmd_pos)
{
	int	cur_pipe[2];
	int	child_pid;

	cur_pipe[0] = -1;
	cur_pipe[1] = -1;
	initialize_io(mbox, cmd_node, cmd_pos);
	if (cmd_pos == SINGLE_CMD && is_cmd_builtin(mbox, cmd_node->content))
		return (run_single_builtin(mbox));
	else
	{
		setup_use_pipe(mbox, cmd_pos);
		if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
			if (pipe(cur_pipe) < 0)
				return (destroy_mbox_with_exit(mbox, EXIT_FAILURE));
		mbox->exec.pid[mbox->exec.pid_index] = fork();
		child_pid = mbox->exec.pid[mbox->exec.pid_index];
		if (child_pid < 0)
			return (destroy_mbox_with_exit(mbox, EXIT_FAILURE));
		conf_sig_handler(SIG_STATE_PARENT);
		if (child_pid == 0)
			exec_child(mbox, cmd_node, cur_pipe);
		else
			return (exec_parent(mbox, cur_pipe, cmd_node, child_pid));
	}
	return (ft_true);
}

static void	wait_for_execution(t_mbox *mbox)
{
	int		i;
	int		exit_status;

	i = -1;
	exit_status = 0;
	if (mbox->exec.pid_index != 0)
	{
		while (++i < cmd_counter(mbox->ast))
			waitpid(mbox->exec.pid[i], &exit_status, 0);
		if (g_signal_status == 0)
		{
			if (WIFEXITED(exit_status))
				set_var_value_int(mbox, "?", WEXITSTATUS(exit_status));
			else if (WIFSIGNALED(exit_status))
				set_var_value_int(mbox, "?", exit_status + 128);
		}
	}
}

/**
 * @brief	traverses trough the AST checks cmd POSITION
 * 
 * 			EXAMPLES:
 *      	SINGLE          ls -l
 * 
 *          	    FIRST       MIDDLE          LAST
 *      	input:  ls -l   | grep "Makefile" | wc -l
 * 			
 * 			then calls 'execute_cmd' with the corresponding flag and waits for
 * 			all the child processes to be finished
 * @param	mbox 
 * @return	t_bool 
 */
void	execute(t_mbox *mbox)
{
	t_ast	*cur;

	info_print_executor_banner(mbox, ft_true, GREEN);
	if (!allocate_pid_array(mbox))
		return ;
	cur = mbox->ast;
	if (cur->type == CMD_NODE)
	{
		if (!execute_cmd(mbox, cur, SINGLE_CMD))
			return ;
	}
	else
	{
		if (!execute_cmd(mbox, cur->left, FIRST_CMD))
			return ;
		while (cur->right->type == PIPE_NODE)
		{
			cur = cur->right;
			if (!execute_cmd(mbox, cur->left, MIDDLE_CMD))
				return ;
		}
		if (!execute_cmd(mbox, cur->right, LAST_CMD))
			return ;
	}
	wait_for_execution(mbox);
	info_print_executor_banner(mbox, ft_false, GREEN); 
}
