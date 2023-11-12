/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/12 04:37:06 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: rename file to cmd_system and the other one to cmd_builtin


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

	if(!path)
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
 * @param mbox 
 * @param cmd 
 * @param i 
 * @return char* 
 */
char    *get_abs_cmd_path(t_mbox *mbox, char *cmd)
{
	char    **path_dirs;
	char	*path;
	int 	i;

	// check if cmd is a path like ./hw.sh
	if (!access(cmd, X_OK))
			return (ft_strdup(cmd));

	// try to find a working path at the PATH variable
	path_dirs = ft_split(get_var_value(mbox, "PATH"), ':');
	if (!path_dirs) // NO PATH VARIALE so no change to find an absolute path (CASE: unset PATH)
		return (NULL);
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
	return (path);
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
char **args_to_matrix(t_mbox *mbox, char *cmd, t_ast *arg_node)
{
	char	**av;
	char    *args_str;
	char	*lim_split;
	char	*lim_null;

	av = NULL;
	args_str = seperate_cmd_from_path(cmd, ft_false);
	if (!args_str)
		return (av);
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
	av = ft_split(args_str, add_offset('+'));
	int i = -1;
	while(av[++i])
	{
		if(str_cmp_strct(av[i], lim_null))
		{
			free(av[i]);
			av[i] = "\0";
		}
	}
	free_whatever("ppp", args_str, lim_null, lim_split);
	return(av);
}
