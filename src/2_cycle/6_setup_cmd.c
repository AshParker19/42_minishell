/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_setup_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:46:17 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 14:09:07 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"


/**
 * @brief this function will be called by 'conf_parent'
 *          if the cmd has a hd it makes the parent wait for the child to finish
 * 
 */
static t_bool	hd_parent_wait(t_mbox *mbox, int *cur_p, t_ast *node_cpy, int kid_pid)
{
	int	exit_status;

	exit_status = 0;
	while (node_cpy->left)
	{
		node_cpy = node_cpy->left;
		if (node_cpy->type == RED_IN_HD)
		{
			conf_sig_handler(SIG_STATE_IGNORE);
			waitpid(kid_pid, &exit_status, 0);
			conf_sig_handler(SIG_STATE_PARENT);
			set_var_value_int(mbox, "?", WEXITSTATUS(exit_status));
			if (exit_status != EXIT_SUCCESS)
			{
				if (cur_p[P_LEFT] != -1)
					close(cur_p[P_LEFT]);
				if (cur_p[P_RIGHT] != -1)
					close(cur_p[P_RIGHT]);
				g_signal_status = SIGNAL_EXIT_HD;
				return (ft_false);
			}
			return (ft_true);
		}
	}
	return (ft_true);
}

static t_bool	setup_single_builtin(t_mbox *mbox)
{
	if (!setup_redirs(mbox, mbox->ast->left, NULL))
	{
		if (mbox->exec.io.cmd_fd[CMD_IN] != -1)
			close (mbox->exec.io.cmd_fd[CMD_IN]);
		if (mbox->exec.io.cmd_fd[CMD_OUT] != -1)
			close (mbox->exec.io.cmd_fd[CMD_OUT]);
		mbox->exec.io.cmd_fd[CMD_IN] = -1;
		mbox->exec.io.cmd_fd[CMD_OUT] = -1;
		return (ft_false);
	}
	if (mbox->exec.io.cmd_fd[CMD_IN] == -1)
		mbox->exec.io.cmd_fd[CMD_IN] = STDIN_FILENO;
	if (mbox->exec.io.cmd_fd[CMD_OUT] == -1)
		mbox->exec.io.cmd_fd[CMD_OUT] = STDOUT_FILENO; 
	run_cmd_builtin(mbox, mbox->ast, ft_true);
	if (mbox->exec.io.cmd_fd[CMD_IN] != STDIN_FILENO)
		close (mbox->exec.io.cmd_fd[CMD_IN]);
	if (mbox->exec.io.cmd_fd[CMD_OUT] != STDOUT_FILENO)
		close (mbox->exec.io.cmd_fd[CMD_OUT]);
	mbox->exec.io.cmd_fd[CMD_IN] = -1;
	mbox->exec.io.cmd_fd[CMD_OUT] = -1;
	close_process_fds(mbox);
	return (ft_true);
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
		return (setup_single_builtin(mbox));
	else
	{
		conf_pipe(mbox, cmd_pos);
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
	redir_pipe(mbox, cur_p);
	if (!setup_redirs(mbox, cmd_node->left, cur_p))
	{
		if (cmd_node->cmd_pos == FIRST_CMD || cmd_node->cmd_pos == MIDDLE_CMD)
			close(cur_p[P_RIGHT]);
		if (cmd_node->cmd_pos != FIRST_CMD
			&& mbox->exec.io.prev_pipe[P_RIGHT] != -1)
			close(mbox->exec.io.prev_pipe[P_RIGHT]);
		destroy_mbox(mbox);
	}
	connect_child_fds(mbox);
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
	close_process_fds(mbox);
	cmd_node_cpy = node;
	return (hd_parent_wait(mbox, cur_p, cmd_node_cpy, kid_pid));
}
