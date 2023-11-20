/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:45:50 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/20 14:39:54 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    save_history(t_mbox *mbox, char *inp)
{
	t_history   *new_hist;
	static int  i;
	
	new_hist = ft_calloc(1, sizeof(t_history));
	if (!new_hist)
		return ;
	new_hist->inp = ft_strdup(inp);
	new_hist->index = ++i;
	new_hist->mbox = mbox;
	if (!mbox->history)
	{
		mbox->history = new_hist;
		mbox->history->lst = ft_lstnew(new_hist);
	}
	else
		ft_lstadd_back(&(mbox->history->lst), ft_lstnew(new_hist));
}

void    builtin_history(t_mbox *mbox, t_ast *arg_node)
{
	(void)arg_node;
	ft_lstiter(mbox->history->lst, print_history_node);
	set_var_value(mbox, "?", EXIT_SUCCESS_STR);
}

