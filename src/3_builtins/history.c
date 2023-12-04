/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:45:50 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/04 18:34:46 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief only used via 'ft_lstiter' in 'builtin_history'
 * 		  prints the info from each node to the output, the same way bash does
 * 
 * @param content 
 */
void	print_history_node(void *content)
{
	t_history	*node;

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
 * 		  frees the content of each node and then the node itself
 * 
 * @param content 
 */
void	del_history_node(void *content)
{
	t_history	*node;

	node = (t_history *)content;
	if (node)
	{
		if (node->inp)
			free (node->inp);
		free(node);
	}
}

/**
 * @brief	being called from main to store each not emty input string.
 * 			allocates a new node, fills with a needed info and puts it at
 * 			the end of the linked list
 * 
 * @param	mbox 
 * @param	inp 
 */
void	save_history(t_mbox *mbox)
{
	t_history	*new_node;
	static int	i;

	new_node = ft_calloc(1, sizeof(t_history));
	if (!new_node)
		return ;
	new_node->inp = ft_strdup(mbox->inp_trim); 
	new_node->index = ++i;
	new_node->mbox = mbox;
	ft_lstadd_back(&(mbox->history_lst), ft_lstnew(new_node));
}

/**
 * @brief	iterates through the history and prints all the info
 * 
 * @param	mbox 
 * @param	arg_node 
 */
void	builtin_history(t_mbox *mbox, t_ast *arg_node)
{
	(void)arg_node;
	ft_lstiter(mbox->history_lst, print_history_node);
	set_var_value(mbox, "?", EXIT_SUCCESS_STR);
}
