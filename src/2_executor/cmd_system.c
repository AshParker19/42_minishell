/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_system.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/04 23:23:47 by astein           ###   ########.fr       */
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

/**
 * @brief 		NOTE: MALLOCS!
 * 
 * 				TODO: maybe move to general utils maybe make static?
 * 
 * 				/usr/bin/ls -> ls
 * 				./hw.sh		-> hw.sh
 * 
 * @param cmd 
 * @return char* 
 */
char	*seperate_cmd_from_path(char *path, t_bool free_path)
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
	char	**path_dirs;
	char	*path;
	int		i;

	path = NULL;
	if (!*cmd)	
	{
		err_msg(mbox, 127, "nnnn", ERR_P, "''", CS, CMD_N_FND);
		return (NULL);
	}
	if (!ft_strchr(cmd, '/'))
	{
		
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
	}
	if (path)
		return (path);
	return (temp_run_cmd_system_error(mbox, cmd));
}

char	**tmp_freer(char *args_str, char *lim_null)
{
	int		i;
	char	**av;

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
	return (av);
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
char	**args_to_matrix(t_mbox *mbox, char *cmd, t_ast *arg_node)
{
	char	**av;
	char	*args_str;
	char	*lim_split;
	char	*lim_null;

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
	av = tmp_freer(args_str, lim_null);
	free_whatever("ppp", args_str, lim_null, lim_split);
	return (av);
}
