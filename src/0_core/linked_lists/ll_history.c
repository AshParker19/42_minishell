/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:31:19 by astein            #+#    #+#             */
/*   Updated: 2023/11/18 17:44:50 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief only used via 'ft_lstiter' in 'builtin_history'
 * 
 * @param content 
 */
void    print_history_node(void *content)
{
	t_history   *node;

	node = (t_history *)content;
	if (node)
	{
		ft_putstr_fd("  ", node->mbox->executor.io.cmd_fd[CMD_OUT]);
		ft_putnbr_fd(node->index, node->mbox->executor.io.cmd_fd[CMD_OUT]);
		ft_putstr_fd("  ", node->mbox->executor.io.cmd_fd[CMD_OUT]);
		ft_putendl_fd(node->inp, node->mbox->executor.io.cmd_fd[CMD_OUT]);
	}
}
/**
 * @brief only used via 'ft_lstclear' in 'free_history'
 * 
 * @param content 
 */
void    del_history_node(void *content)
{
    t_history   *node;

    node = (t_history *)content;
    if (node)
	{
		if (node->inp)
			free (node->inp);
		free(node);
	}	
}
