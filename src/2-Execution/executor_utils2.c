/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/07 14:01:45 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *find_cmd(t_minibox *minibox, char *cmd, int i)
{
    int     check;
    char    *path;
    
    if (ft_strchr(cmd, '/'))
    {
        check = access(cmd, F_OK);
        if (!check)
            return (ft_strdup(cmd));
        return (NULL);    
    }
    while (minibox->executor.path_dirs[++i])
    {
        path = ft_strjoin_slash(cmd, minibox->executor.path_dirs[i]);
        check = access(path, F_OK);
        if (!check)
            return (path);
        else
            free (path);    
    }
    return (NULL);
}

char	*ft_strjoin_slash(char *src, char *dest)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
		j++;
	path = malloc(i + j + 2);
	if (!path)
		return (NULL);
	i = -1;
	while (dest[++i])
		path[i] = dest[i];
	path[i++] = '/';
	j = -1;
	while (src[++j])
	{
		path[i] = src[j];
		i++;
	}
	path[i] = 0;
	return (path);
}

void get_cmd_av(t_minibox *minibox, t_tree *root)
{
    char    *args;
    char    *temp;
    
    if (!root && !root->content)
        return ;
    args = root->content;
    while (root->right)
    {
        if (root->right->content)
        {
            temp = ft_strcat_multi(3, args, "|", root->right->content);
            free (args);
            args = temp;
        }
        root = root->right;
    }
    minibox->executor.cmd_av = ft_split(args, '|');
}
