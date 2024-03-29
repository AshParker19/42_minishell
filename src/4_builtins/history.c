/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:45:50 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/18 02:04:23 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

static void	print_history_node(void *content)
{
	t_history	*node;

	node = (t_history *)content;
	if (node)
	{
		ft_putstr_fd("  ", node->mbox->exec.io.cmd_fd[CMD_OUT]);
		ft_putnbr_fd(node->index, node->mbox->exec.io.cmd_fd[CMD_OUT]);
		ft_putstr_fd("  ", node->mbox->exec.io.cmd_fd[CMD_OUT]);
		ft_putendl_fd(node->inp, node->mbox->exec.io.cmd_fd[CMD_OUT]);
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
	new_node->inp = ft_strdup(mbox->inp_orig);
	new_node->index = ++i;
	new_node->mbox = mbox;
	ft_lstadd_back(&(mbox->history_lst), ft_lstnew(new_node));
}

/**
 * @brief   The builtin `history` outputs all previous user input
 * 			in a numbered list.
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#history-builtin
 * @param   mbox        
 * @param   arg_node    
 */
void	builtin_history(t_mbox *mbox, t_ast *arg_node)
{
	(void)arg_node;
	ft_lstiter(mbox->history_lst, print_history_node);
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
}
