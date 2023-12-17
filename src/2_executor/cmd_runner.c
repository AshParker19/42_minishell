/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:09:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/17 16:58:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief	checks if the command node exists and has a value
 * 			if so it runs the cmd either via
 * 				- 'run_cmd_builtin' or
 *	 			- 'run_cmd_system'
 * 
 * @param	mbox		
 * @param	cmd_node	
 */
void	run_cmd_main(t_mbox *mbox, t_ast *cmd_node)
{
	if (!cmd_node || !cmd_node->content)
		return ;
	if (mbox->exec.io.cmd_fd[CMD_IN] != -1)
		close(mbox->exec.io.cmd_fd[CMD_IN]);
	if (mbox->exec.io.cmd_fd[CMD_OUT] != -1)
		close(mbox->exec.io.cmd_fd[CMD_OUT]);
	if (is_cmd_builtin(mbox, cmd_node->content))
		run_cmd_builtin(mbox, cmd_node, ft_false);
	else
		run_cmd_system(mbox, cmd_node);
}

void	run_cmd_system(t_mbox *mbox, t_ast *cmd_node)
{
	char	*abs_cmd_path;
	char	**cur_env;
	char	**cur_av;

	abs_cmd_path = NULL;
	cur_env = NULL;
	cur_av = NULL;
	abs_cmd_path = get_abs_cmd_path(mbox, cmd_node->content);
	if (!abs_cmd_path)
		return ;
	cur_env = env_to_matrix(mbox, NULL);
	cur_av = args_to_matrix(mbox, abs_cmd_path, cmd_node->right);
	if (cur_av)
		execve(abs_cmd_path, cur_av, cur_env);
	if (abs_cmd_path)
		free (abs_cmd_path);
	free_whatever("mm", cur_env, cur_av);
}

/**
 * @brief   traverses through the ll and run builtin cmd via corresponding
 *          function pointer
 * 
 * @param   mbox 
 * @param   cmd_node 
 */
void	run_cmd_builtin(t_mbox *mbox, t_ast *cmd_node, t_bool parent)
{
	int	i;

	i = -1;
	if (!parent)
	{
		mbox->exec.io.cmd_fd[CMD_IN] = STDIN_FILENO;
		mbox->exec.io.cmd_fd[CMD_OUT] = STDOUT_FILENO; 
	}
	while (mbox->exec.builtins[++i].cmd_name)
	{
		if (str_cmp_strct(mbox->exec.builtins[i].cmd_name,
				cmd_node->content))
			mbox->exec.builtins[i].func_name(mbox, cmd_node->right);
	}
}

t_bool	run_single_builtin(t_mbox *mbox)
{
	if (!configure_redir(mbox, mbox->ast->left, NULL))
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
	close_process_fds_v2(mbox);
	return (ft_true);
}
