/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_execute_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:19:44 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 12:52:19 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

static t_bool	allocate_pid_array(t_mbox *mbox)
{
	mbox->exec.pid = ft_calloc(cmd_counter(mbox->ast), sizeof(int));
	if (!mbox->exec.pid)
		return (ft_false);
	return (ft_true);
}

/**
 * @brief   called by 'execute_ast' after all the cmds have been executed to
 * 			wait for all the child processes to be finished
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
 * @brief	traverses trough the AST checks cmd POSITION
 * 
 * 			EXAMPLES:
 *      	SINGLE          ls -l
 * 
 *          	    FIRST       MIDDLE          LAST
 *      	input:  ls -l   | grep "Makefile" | wc -l
 * 			
 * 			then calls 'setup_cmd' with the corresponding flag and waits for
 * 			all the child processes to be finished
 * @param	mbox 
 * @return	t_bool 
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
