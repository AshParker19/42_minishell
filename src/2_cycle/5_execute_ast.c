/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_execute_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 22:02:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief   This file is the starting point of the execution. It calls all the
 * 			functions needed to setup redirections, pipes and the execution of
 * 			the commands.
 * 
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/docs/documentation.md#executing
 */

#include "frankenshell.h"

/**
 * @brief   Before we start to execute we need to allocate the pid array so we
 * 			can store the pids of all the child processes. The array is used in
 * 			'wait_for_execution' to wait for all the child processes to be
 * 			finished
 * 
 * @param   mbox        
 * @return  t_bool      
 */
static t_bool	allocate_pid_array(t_mbox *mbox)
{
	mbox->exec.pid = ft_calloc(cmd_counter(mbox->ast), sizeof(int));
	if (!mbox->exec.pid)
		return (ft_false);
	return (ft_true);
}

/**
 * @brief   called by 'execute_ast' after all the child processes have been
 * 			forked. This function uses the pid array in which all the child
 * 			processes pids are stored. It uses the pid array to wait for all
 * 			the child processes to be finished. It also updates the exit status.
 * 
 * @param   mbox        
 */
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
 * @brief   traverses trough the AST.
 * 
 * 			(SINGLE_CMD)
 * 			If the root is an cmd, no pipe is needed and the function call
 * 			'setup_cmd' with the corresponding flag will process the cmd.
 * 
 * 			If the root is a pipe node the function will:
 * 			- (FIRST_CMD) once: 
 * 				- call the function 'setup_cmd' with the corresponding flag for
 * 					the first cmd in the expression.
 * 			- (MIDDLE_CMD) until the second last cmd is reached: 
 * 				- call the function 'setup_cmd' with the corresponding flag for
 * 					the middle cmd in the expression.
 * 			- (LAST_CMD) once: 
 * 				- call the function 'setup_cmd' with the corresponding flag for
 * 					the last cmd in the expression.
 * 
 * 			In any case the function 'wait_for_execution' will be called to wait
 * 			for all the child processes to be finished.
 * 
 * 			EXAMPLES:
 * 
 * 			FLAG:	SINGLE_CMD	FIRST_CMD	MIDDLE_CMD			LAST_CMD
 * 			INPUT:	ls -l
 *      	INPUT:	echo HI
 * 			INPUT:  			ls -l	| 	grep "Makefile" | 	wc -l
 *      	
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/docs/documentation.md#executing
 * 
 * @param   mbox        
 */
void	execute_ast(t_mbox *mbox)
{
	t_ast	*cur;

	info_print_executor_banner(mbox, ft_true, GREEN);
	if (!allocate_pid_array(mbox))
		return ;
	cur = mbox->ast;
	if (cur->type == CMD_NODE)
	{
		if (!setup_cmd(mbox, cur, SINGLE_CMD))
			return ;
	}
	else
	{
		if (!setup_cmd(mbox, cur->left, FIRST_CMD))
			return ;
		while (cur->right->type == PIPE_NODE)
		{
			cur = cur->right;
			if (!setup_cmd(mbox, cur->left, MIDDLE_CMD))
				return ;
		}
		if (!setup_cmd(mbox, cur->right, LAST_CMD))
			return ;
	}
	wait_for_execution(mbox);
	info_print_executor_banner(mbox, ft_false, GREEN); 
}

/**
 * @brief   called by 'reset_cycle' to free pid array which was allocated
 * 			via 'allocate_pid_array'
 * 
 * @param   mbox        
 */
void	free_process(t_mbox *mbox)
{
	if (mbox->exec.pid)
	{
		free (mbox->exec.pid);
		mbox->exec.pid = NULL;
	}
}
