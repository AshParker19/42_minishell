/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:09:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/08 01:35:46 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


/*
	decides if the command to be executed is a builtin cmd or a system cmd

	ALWAYS PERFORED IN CHILD
*/

/**
 * @brief	checks if the command node exists and has a value
 * 			if so it runs the cmd either via
 * 				- 'run_cmd_builtin' or
 *	 			- 'run_cmd_system'
 * 
 * @param	mbox		
 * @param	cmd_node	
 */
void    run_cmd_main(t_mbox *mbox, t_ast *cmd_node)
{
	if (!cmd_node || !cmd_node->content)
		return ; // TODO: DO WE NEED TO EXIT THE CHILD? IS IT AWAYS A CHILD?
	if (is_cmd_builtin(mbox, cmd_node->content))
		run_cmd_builtin(mbox, cmd_node);
	else
		run_cmd_system(mbox, cmd_node);
}

void    run_cmd_system(t_mbox *mbox, t_ast *cmd_node)
{
	char	*error_msg;
	char	*abs_cmd_path;
	char	**cur_env;
	
	cur_env = NULL;
	if (mbox->executor.io.cmd_fd[CMD_IN] != -1)
		close(mbox->executor.io.cmd_fd[CMD_IN]);
	if (mbox->executor.io.cmd_fd[CMD_OUT] != -1)
		close(mbox->executor.io.cmd_fd[CMD_OUT]);
	abs_cmd_path = NULL;
	get_cmd_av(mbox, cmd_node);
	if (mbox->executor.cmd_av)
	{
		abs_cmd_path = get_cmd_path(mbox, cmd_node->content, -1, ft_true);
		cur_env = env_to_matrix(mbox);
		execve(abs_cmd_path, mbox->executor.cmd_av, cur_env);
	}
	free_whatever("mp", cur_env, abs_cmd_path);
	put_err_msg("nnnn", ERR_PROMT, "command '", cmd_node->content, "' not found");
	err_free_and_close_box(mbox, 127);
}

/**
 * @brief   traverses through the ll and run builtin cmd via corresponding
 *          function pointer
 * 
 * @param   mbox 
 * @param   cmd_node 
 */
void    run_cmd_builtin(t_mbox *mbox, t_ast *cmd_node)
{
    int i;
    
    i = -1;
    while (mbox->executor.builtins[++i].cmd_name)
        if (str_cmp_strct(mbox->executor.builtins[i].cmd_name, cmd_node->content))
            mbox->executor.builtins[i].func_name(mbox, cmd_node->right);
}

t_bool run_single_builtin(t_mbox *mbox)
{
	mbox->executor.io.cmd_fd[CMD_IN] = STDIN_FILENO;
	mbox->executor.io.cmd_fd[CMD_OUT] = STDOUT_FILENO;
	if (!configure_redir(mbox, mbox->root->left))
	{
		// TODO: does all of the if makes sence?
		if (mbox->executor.io.cmd_fd[CMD_IN] != STDIN_FILENO)
			close (mbox->executor.io.cmd_fd[CMD_IN]);
		if (mbox->executor.io.cmd_fd[CMD_OUT] != STDOUT_FILENO)
			close (mbox->executor.io.cmd_fd[CMD_OUT]);  
		mbox->executor.io.cmd_fd[CMD_IN] = -1;
		mbox->executor.io.cmd_fd[CMD_OUT] = -1;
		return (ft_false);
	}
	run_cmd_builtin(mbox, mbox->root);  // we should make builtins return bool, if it false, set exit status as EXIT_FAILURE
	if (mbox->executor.io.cmd_fd[CMD_IN] != STDIN_FILENO)
		close (mbox->executor.io.cmd_fd[CMD_IN]);
	if (mbox->executor.io.cmd_fd[CMD_OUT] != STDOUT_FILENO)
		close (mbox->executor.io.cmd_fd[CMD_OUT]);  
	mbox->executor.io.cmd_fd[CMD_IN] = -1;
	mbox->executor.io.cmd_fd[CMD_OUT] = -1;
	set_var_value(mbox, "?", ft_itoa(EXIT_SUCCESS));
	close_process_fds_v2(mbox);
	free_cycle_v2(mbox);
	return (ft_true);
}

