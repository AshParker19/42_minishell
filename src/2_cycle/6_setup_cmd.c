/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_setup_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:46:17 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 22:15:46 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/docs/documentation.md#setup-command
 */

#include "frankenshell.h"

/**
 * @brief   This function will be called by 'conf_parent'
 *          If the cmd has a hd it makes the parent wait for the child to finish
 * 
 * @param   mbox        
 * @param   cur_p       
 * @param   node_cpy    
 * @param   kid_pid     
 * @return  t_bool      
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

/**
 * @brief   Here the child process is configured. Therefore the child will be
 * 			connected to the pipe first. Then the redirections will be setup.
 * 			And finally the command will be executed via 'run_cmd_main'.
 * 
 * @param   mbox        
 * @param   cmd_node    
 * @param   cur_p       
 */
static void	conf_child(t_mbox *mbox, t_ast *cmd_node, int *cur_p)
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

static t_bool	conf_parent(t_mbox *mbox, int *cur_p, t_ast *node, int kid_pid)
{
	t_ast	*cmd_node_cpy;

	if (node->cmd_pos == FIRST_CMD || node->cmd_pos == MIDDLE_CMD)
		close(cur_p[P_LEFT]);
	if (node->cmd_pos != FIRST_CMD && node->cmd_pos != SINGLE_CMD)
		close(mbox->exec.io.prev_pipe[P_RIGHT]);
	mbox->exec.pid_index++;
	mbox->exec.io.prev_pipe[P_RIGHT] = cur_p[P_RIGHT];
	mbox->exec.io.prev_pipe[P_LEFT] = cur_p[P_LEFT];
	close_fds(mbox);
	cmd_node_cpy = node;
	return (hd_parent_wait(mbox, cur_p, cmd_node_cpy, kid_pid));
}

/**
 * @brief   This function considers the command position ('cmd_pos') and sets up
 * 			the pipe and fork if needed. The parent and child will then be
 * 			handled by the functions 'conf_parent' and 'conf_child'.
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/docs/documentation.md#setup-command
 * 
 * @param   mbox        
 * @param   cmd_node    
 * @param   cmd_pos     
 * @return  t_bool      
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
