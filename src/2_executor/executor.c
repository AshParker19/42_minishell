/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2023/11/12 03:23:00 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void perform_child(t_mbox *mbox, t_ast *cmd_node, int cmd_pos, int *cur_pipe)
{
	update_signals(SIGNAL_CHILD);
	if (cmd_pos == SINGLE_CMD && str_cmp_strct("./minishell",
		cmd_node->content))
		increment_shlvl(mbox);
	if (is_cmd_builtin(mbox, cmd_node->content))
	{
		mbox->executor.io.cmd_fd[CMD_IN] = STDIN_FILENO;
		mbox->executor.io.cmd_fd[CMD_OUT] = STDOUT_FILENO;
	}
	setup_pipes(mbox, cur_pipe);
	if (!configure_redir(mbox, cmd_node->left))
	{
		// if (cur_pipe[P_RIGHT] != -1) //FIXME: 
		// // CASE 1 Heredoc 
		// // CASE 2 file without permissions
		// 	close(cur_pipe[P_RIGHT]);
		free_and_close_box_v2(mbox);
	}
	setup_process_std(mbox);
	if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		close(cur_pipe[P_RIGHT]);
	if (cmd_pos != FIRST_CMD && mbox->executor.io.prev_pipe[P_RIGHT] != -1)
		close(mbox->executor.io.prev_pipe[P_RIGHT]);
	run_cmd_main(mbox, cmd_node);
	free_and_close_box_v2(mbox);
}

static void	perform_parent(t_mbox *mbox, int cmd_pos, int *cur_pipe)
{
	if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		close(cur_pipe[P_LEFT]);
	if (cmd_pos != FIRST_CMD && cmd_pos != SINGLE_CMD)
		close(mbox->executor.io.prev_pipe[P_RIGHT]);
	mbox->executor.pid_index++;
	mbox->executor.io.prev_pipe[P_RIGHT] = cur_pipe[P_RIGHT];
	mbox->executor.io.prev_pipe[P_LEFT] = cur_pipe[P_LEFT];
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
static t_bool    execute_cmd(t_mbox *mbox, t_ast *cmd_node, int cmd_pos)
{
	int cur_pipe[2];

	initialize_io(mbox);
	if (cmd_pos == SINGLE_CMD && is_cmd_builtin(mbox, cmd_node->content))
		return (run_single_builtin(mbox));
	else
	{
		setup_use_pipe(mbox, cmd_pos);
		if (cmd_pos == FIRST_CMD || cmd_pos == MIDDLE_CMD)
		{
			if (pipe(cur_pipe) < 0)
				err_free_and_close_box(mbox, EXIT_FAILURE);    
		}
		mbox->executor.pid[mbox->executor.pid_index] = fork();
		if (mbox->executor.pid[mbox->executor.pid_index] < 0)
			err_free_and_close_box(mbox, EXIT_FAILURE);    
		update_signals(SIGNAL_PARENT);
		if (mbox->executor.pid[mbox->executor.pid_index] == 0)
			perform_child(mbox, cmd_node, cmd_pos, cur_pipe);
		else
			perform_parent(mbox, cmd_pos, cur_pipe);
	}
	return (ft_true);
}

static void    wait_for_execution(t_mbox *mbox)
{
	int 	i;
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
			{
				set_var_value_int(mbox, "?", WEXITSTATUS(exit_status));
				put_info_msg(mbox, "nynn", "exit status:", ft_itoa(WEXITSTATUS(exit_status)), "lol", "|");
			}
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
t_bool    execute(t_mbox *mbox) //TODO: do exit for builtins
{   
	t_ast  *cur;
	
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
		execute_cmd(mbox, cur->left, FIRST_CMD); //TODO: check if execute_cmd doesn't return false, check it at all of calls
		while (cur->right->type == PIPE_NODE)
		{
			cur = cur->right;
			execute_cmd(mbox, cur->left, MIDDLE_CMD); //TODO: check if execute_cmd doesn't return false,
		}
		execute_cmd(mbox, cur->right, LAST_CMD);    //TODO: check if execute_cmd doesn't return false,
	}
	wait_for_execution(mbox);
	return (ft_true);
}

