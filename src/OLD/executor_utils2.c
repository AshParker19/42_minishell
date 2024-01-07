/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:48:08 by anshovah          #+#    #+#             */
/*   Updated: 2024/01/07 12:48:24 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

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

static char	*get_abs_cmd_path_from_var(t_mbox *mbox, char *cmd)
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
char	*get_abs_cmd_path(t_mbox *mbox, char *cmd)
{
	char	*path;

	path = NULL;
	if (!*cmd)
	{
		err_msg(mbox, 127, "nnnn", ERR_P, "''", CS, CMD_N_FND);
		return (NULL);
	}
	if (!ft_strchr(cmd, '/'))
		path = get_abs_cmd_path_from_var(mbox, cmd);
	if (path)
		return (path);
	return (temp_run_cmd_system_error(mbox, cmd));
}

/**
 * @brief this function will be called by 'conf_parent'
 *          if the cmd has a hd it makes the parent wait for the child to finish
 * 
 */
t_bool	hd_parent_wait(t_mbox *mbox, int *cur_p, t_ast *node_cpy, int kid_pid)
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
