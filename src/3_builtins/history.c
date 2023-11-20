/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:45:50 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/20 23:36:03 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

void    save_history(t_mbox *mbox, char *inp)
{
	t_history   *new_node;
	static int  i;
	
	new_node = ft_calloc(1, sizeof(t_history));
	if (!new_node)
		return ;
	new_node->inp = ft_strdup(inp);
	new_node->index = ++i;
	new_node->mbox = mbox;
	ft_lstadd_back(&(mbox->history_lst), ft_lstnew(new_node)); // are we sure we want to use it this way? it's now one more memory allocation for each of the nodes
}

void    builtin_history(t_mbox *mbox, t_ast *arg_node)
{
	(void)arg_node;
	ft_lstiter(mbox->history_lst, print_history_node);
	set_var_value(mbox, "?", EXIT_SUCCESS_STR);
}
