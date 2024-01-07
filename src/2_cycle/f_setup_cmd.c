/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_setup_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:46:17 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 12:51:40 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief	recursively traverses through the AST and counts the amount
 * 			of command nodes
 * 
 * @param	ast_node 
 * @return	int 
 */
int	cmd_counter(t_ast *ast_node)
{
	if (!ast_node)
		return (0);
	if (ast_node->type == CMD_NODE)
		return (1);
	return (1 + cmd_counter(ast_node->right));
}

/**
 * @brief	
 * 
 * @param	mbox 
 * @param	cmd_node 
 * @param	cmd_pos 
 * @return	t_bool 
 */
t_bool	setup_cmd(t_mbox *mbox, t_ast *cmd_node, int cmd_pos)
{
	int	cur_pipe[2];
	int	child_pid;

	cur_pipe[0] = -1;
	cur_pipe[1] = -1;
	initialize_fds(mbox, cmd_node, cmd_pos);
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
			conf_child(mbox, cmd_node, cur_pipe);
		else
			return (conf_parent(mbox, cur_pipe, cmd_node, child_pid));
	}
	return (ft_true);
}

void	conf_child(t_mbox *mbox, t_ast *cmd_node, int *cur_p)
{
	if (is_cmd_builtin(mbox, cmd_node->content))
		conf_sig_handler(SIG_STATE_CHILD_BUILTIN);
	else
		conf_sig_handler(SIG_STATE_CHILD);
	setup_pipes(mbox, cur_p);
	if (!setup_redirs(mbox, cmd_node->left, cur_p))
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

t_bool	conf_parent(t_mbox *mbox, int *cur_p, t_ast *node, int kid_pid)
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
