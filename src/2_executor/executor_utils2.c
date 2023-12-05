/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:48:08 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/05 13:55:57 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	if (ft_strchr(cmd, '/')  && S_ISDIR(path_stat.st_mode))
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

static char *get_abs_cmd_path_from_var(t_mbox *mbox, char *cmd)
{
	char	**path_dirs;
	int		i;
    char    *path;

	path = NULL;
    path_dirs = ft_split(get_var_value(mbox, "PATH"), ':');
    if (path_dirs) // NO PATH VARIALE so no change to find an absolute path (CASE: unset PATH)
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
