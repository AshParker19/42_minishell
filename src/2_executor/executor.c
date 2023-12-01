/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/12/01 16:05:10 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_mbox *mbox, t_ast *cmd_node, int cmd_pos, int *cur_p)
{
	update_signals(SIGNAL_CHILD);
	setup_pipes(mbox, cur_p);
	if (!configure_redir(mbox, cmd_node->left))
	{
		if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
			close(cur_p[P_RIGHT]);
		if (cmd_pos != FIRST_CMD && mbox->executor.io.prev_pipe[P_RIGHT] != -1)
			close(mbox->executor.io.prev_pipe[P_RIGHT]);
		free_and_close_box_v2(mbox);
	}
	setup_process_std(mbox);
	if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		close(cur_p[P_RIGHT]);
	if (cmd_pos != FIRST_CMD && mbox->executor.io.prev_pipe[P_RIGHT] != -1)
		close(mbox->executor.io.prev_pipe[P_RIGHT]);
	run_cmd_main(mbox, cmd_node);
	free_and_close_box_v2(mbox);
}

static void	exec_parent(t_mbox *mbox, int cmd_pos, int *cur_p)
{
	if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		close(cur_p[P_LEFT]);
	if (cmd_pos != FIRST_CMD && cmd_pos != SINGLE_CMD)
		close(mbox->executor.io.prev_pipe[P_RIGHT]);
	mbox->executor.pid_index++;
	mbox->executor.io.prev_pipe[P_RIGHT] = cur_p[P_RIGHT];
	mbox->executor.io.prev_pipe[P_LEFT] = cur_p[P_LEFT];
	close_process_fds_v2(mbox);
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

	initialize_io(mbox);
	if (cmd_pos == SINGLE_CMD && is_cmd_builtin(mbox, cmd_node->content))
		return (run_single_builtin(mbox));
	else
	{
		setup_use_pipe(mbox, cmd_pos);
		if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
			if (pipe(cur_pipe) < 0)
				return (err_free_and_close_box(mbox, EXIT_FAILURE));
		mbox->executor.pid[mbox->executor.pid_index] = fork();
		if (mbox->executor.pid[mbox->executor.pid_index] < 0)
			return (err_free_and_close_box(mbox, EXIT_FAILURE));
		update_signals(SIGNAL_PARENT);
		if (mbox->executor.pid[mbox->executor.pid_index] == 0)
			exec_child(mbox, cmd_node, cmd_pos, cur_pipe);
		else
			exec_parent(mbox, cmd_pos, cur_pipe);
	}
	return (ft_true);
}

static void	wait_for_execution(t_mbox *mbox)
{
	int		i;
	int		exit_status;
	char	*exit_status_str;

	i = -1;
	if (mbox->executor.pid_index != 0)
	{
		while (++i < cmd_counter(mbox->root))
			waitpid(mbox->executor.pid[i], &exit_status, 0);
		if (g_signal_status == 0)
		{
			//TODO: wait for signal too
			if (WIFEXITED(exit_status))
				set_var_value_int(mbox, "?", WEXITSTATUS(exit_status));
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
void	execute(t_mbox *mbox) //TODO: do exit for builtins
{
	t_ast	*cur;

	if (!allocate_pid_array(mbox))
		return ;
	cur = mbox->root;
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
	print_executor_output(mbox, ft_false); 
}
