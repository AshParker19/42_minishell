/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_system.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/18 16:42:10 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief 		
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
char	**get_args_to_matrix(t_mbox *mbox, char *cmd, t_ast *arg_node)
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
