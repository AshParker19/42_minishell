/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/08 20:43:43 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: rename file to cmd_system and the other one to cmd_builtin

/*
abs = true = full path absoulte path
abs = false = relatvie path*/
char    *get_cmd_path(t_mbox *mbox, char *cmd, int i, t_bool abs)
{
	int     check;
	char    *path;
	char    *path_temp;
	char    **path_dirs;
	
	path_dirs = ft_split(get_var_value(mbox, "PATH"), ':');
	if (!path_dirs)
	{
		put_err_msg("nnn", ERR_PROMT, cmd, ": No such file or directory");
		exit(0);//TODO: check frees and exit status
	}
	path = NULL;
	if (ft_strchr(cmd, '/'))
	{
		check = access(cmd, F_OK);
		if (!check)
			path = ft_strdup(cmd);
	}
	else
	{
		while (path_dirs[++i])
		{
			path = ft_strcat_multi(3, path_dirs[i], "/", cmd);
			check = access(path, F_OK);
			if (!check)
				break ;
			else
			{
				free (path);    
				path = NULL;
			}
		}
	}
	// always null or absolute path
	free_whatever("m", path_dirs);
	if (!path)
		return (NULL);
	else
	{
		if (abs)
			return (path);
		else
		{
			path_temp = ft_strrchr(path, '/');
			path_temp++;
			path_temp = ft_strdup(path_temp);
			free (path);
			return (path_temp);
		}
	}
}

void get_cmd_av(t_mbox *mbox, t_ast *cmd_node)
{
	char    *cur_args_str;
	char    *temp;
	char	*lim_split;
	char	*lim_null;
	
	if (!cmd_node && !cmd_node->content) //TODO: not sure if it need a content
		return ;
	cur_args_str = get_cmd_path(mbox, cmd_node->content, -1, ft_false);
	if (!cur_args_str)
		return ;
	lim_split = ft_chr2str(add_offset('+'));
	lim_null = ft_chr2str(add_offset('-'));
	while (cmd_node->right)
	{
		if (cmd_node->right->content[0] == '\0')
		{
			
			temp = ft_strcat_multi(3, cur_args_str, lim_split, lim_null);
			free (cur_args_str);
			cur_args_str = temp;
		}
		else if (cmd_node->right->content)
		{
			temp = ft_strcat_multi(3, cur_args_str, lim_split,
				cmd_node->right->content);
			free (cur_args_str);
			cur_args_str = temp;
		}
		cmd_node = cmd_node->right;
	}
	mbox->executor.cmd_av = ft_split(cur_args_str, add_offset('+'));
	int i = -1;
	while(mbox->executor.cmd_av[++i])
	{
		if(str_cmp_strct(mbox->executor.cmd_av[i], lim_null))
		{
			free(mbox->executor.cmd_av[i]);
			mbox->executor.cmd_av[i] = "\0";
		}
	}
	free_whatever("ppp", cur_args_str, lim_null, lim_split);
}



