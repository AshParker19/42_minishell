/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/11 22:47:18 by astein           ###   ########.fr       */
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
	
	path = NULL;
	path_dirs = NULL;
	if (ft_strchr(cmd, '/'))
	{
		check = access(cmd, F_OK);
		if (!check)
			path = ft_strdup(cmd);
	}
	else
	{
		path_dirs = ft_split(get_var_value(mbox, "PATH"), ':');
		if (!path_dirs)
		{
			//FIXME: check if we should print the error here
			put_err_msg(mbox, EXIT_FAILURE, "nnn", ERR_PROMPT, cmd, ": No such file or directory");
			exit(0);//TODO: check frees and exit status
		}
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
	char	*lim_split;
	char	*lim_null;
	
	if (!cmd_node && !cmd_node->content) //TODO: not sure if it need a content
		return ;
	dprintf(2, "AHOI\n");
	// cur_args_str = get_cmd_path(mbox, cmd_node->content, -1, ft_false);
	cur_args_str = "./hw";
	dprintf(2, "cmd path: (%s)\n", cur_args_str);
	dprintf(2, "AHOI\n");
	if (!cur_args_str)
		return ;
	lim_split = ft_chr2str(add_offset('+'));
	lim_null = ft_chr2str(add_offset('-'));
	while (cmd_node->right)
	{
		cur_args_str = append_str(cur_args_str, lim_split, ft_false);
		if (cmd_node->right->content[0] == '\0')
			cur_args_str = append_str(cur_args_str, lim_null, ft_false);
		else if (cmd_node->right->content)
			cur_args_str = append_str(cur_args_str, cmd_node->right->content,
				ft_false);
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



