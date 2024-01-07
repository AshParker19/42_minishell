/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:09:02 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 19:37:50 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief 		
 * 
 * 
 * 				/usr/bin/ls -> ls
 * 				./hw.sh		-> hw.sh
 * 
 * @param cmd 
 * @return char* 
 */
static char	*seperate_cmd_from_path(char *path, t_bool free_path)
{
	char	*cmd;

	if (!path)
		return (NULL);
	cmd = ft_strrchr(path, '/');
	cmd++;
	cmd = ft_strdup(cmd);
	if (free_path)
		free(path);
	return (cmd);
}

/**
 * @brief	take all the arg nodes and put them into a char** matrix
 * 			first arg is the paramter 'cmd'
 * 
 * @param mbox 
 * @param cmd 
 * @param arg_node 
 * @return char** 
 */
static char	**get_args_as_matrix(t_mbox *mbox, char *cmd, t_ast *arg_node)
{
	char	**av;
	char	*args_str;
	char	*lim_split;
	char	*lim_null;
	int		i;

	(void)mbox;
	args_str = seperate_cmd_from_path(cmd, ft_false);
	if (!args_str)
		return (NULL);
	lim_split = ft_chr2str(add_offset('+'));
	lim_null = ft_chr2str(add_offset('-'));
	while (arg_node)
	{
		args_str = append_str(args_str, lim_split, ft_false);
		if (arg_node->content[0] == '\0')
			args_str = append_str(args_str, lim_null, ft_false);
		else if (arg_node->content)
			args_str = append_str(args_str, arg_node->content, ft_false);
		arg_node = arg_node->right;
	}
	i = -1;
	av = ft_split(args_str, add_offset('+'));
	while (av[++i])
	{
		if (str_cmp_strct(av[i], lim_null))
		{
			free(av[i]);
			av[i] = "\0";
		}
	}
	free_whatever("ppp", args_str, lim_null, lim_split);
	return (av);
}

/**
 * @brief	as soon as we find one '/' in the string we think its a path
 * 			(or if the path exists via 'access')
 * 
 * 			errno	exitcode	is path
 *					 				if directory
 *					126					cmd is a directory
 *					 				else if is a file
 *					 					if has permissions
 *											we should have executed the file!
 *					 					else
 *			13		126						cmd has no permissions
 *					 				else
 *					127 				127 No such file or directory
 *					 					
 *					 			else
 *					 				127 cmd not found
 * 
 * @param mbox 
 * @param cmd 
 */
static	char	*temp_run_cmd_system_error(t_mbox *mbox, char *cmd)
{
	struct stat	path_stat;

	stat(cmd, &path_stat);
	if (ft_strchr(cmd, '/') && S_ISDIR(path_stat.st_mode))
		err_msg(mbox, 126, "nnnn", ERR_P, cmd, CS, IS_DIR);
	else if (ft_strchr(cmd, '/') && S_ISREG(path_stat.st_mode))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		else
			err_msg(mbox, 126, "nnnn", ERR_P, cmd, CS, NO_PERM);
	}
	else
	{
		if (ft_strchr(cmd, '/'))
			err_msg(mbox, 127, "nnnn", ERR_P, cmd, CS, NO_FOD);
		else if (!*cmd)
			err_msg(mbox, 127, "nnnn", ERR_P, "''", CS, CMD_N_FND);
		else
			err_msg(mbox, 127, "nnn", cmd, CS, CMD_N_FND);
	}
	return (NULL);
}

static char	*get_abs_cmd_path_from_env(t_mbox *mbox, char *cmd)
{
	char	**path_dirs;
	int		i;
	char	*path;

	path = NULL;
	path_dirs = ft_split(get_var_value(mbox, "PATH"), ':');
	if (path_dirs)
	{
		i = -1;
		while (path_dirs[++i])
		{
			path = ft_strcat_multi(3, path_dirs[i], "/", cmd);
			if (!access(path, F_OK))
				break ;
			else
			{
				free (path);
				path = NULL;
			}
		}
		free_whatever("m", path_dirs);
	}
	return (path);
}

/**
 * @brief 	NOTE: MALLOCS!
 * 
 * 			1. check if we find a bin in the PATH variable
 * 				1.1 if yes return the absolute path
 * 			2. check if cmd is a path to a folder
 * 				2.1 if yes return NULL
 * 			3. check if cmd is a path to a file ./hw.sh
 * 				3.1 if yes return the absolute path
 * 
 * @param mbox 
 * @param cmd 
 * @param i 
 * @return char* 
 */
static char	*get_abs_cmd_path(t_mbox *mbox, char *cmd)
{
	char	*path;

	path = NULL;
	if (!*cmd)
	{
		err_msg(mbox, 127, "nnnn", ERR_P, "''", CS, CMD_N_FND);
		return (NULL);
	}
	if (!ft_strchr(cmd, '/'))
		path = get_abs_cmd_path_from_env(mbox, cmd);
	if (path)
		return (path);
	return (temp_run_cmd_system_error(mbox, cmd));
}


static void	run_cmd_system(t_mbox *mbox, t_ast *cmd_node)
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
	cur_env = get_env_as_matrix(mbox, NULL);
	cur_av = get_args_as_matrix(mbox, abs_cmd_path, cmd_node->right);
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
static void	run_cmd_builtin(t_mbox *mbox, t_ast *cmd_node, t_bool parent)
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

t_bool	run_single_builtin(t_mbox *mbox)
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
	close_fds(mbox);
	return (ft_true);
}
