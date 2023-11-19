/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:45:50 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/19 17:08:45 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
	ft_lstadd_back(&(mbox->history_lst), ft_lstnew(new_node));
}

void    builtin_history(t_mbox *mbox, t_ast *arg_node)
{
    (void)arg_node;

	ft_lstiter(mbox->history_lst, print_history_node);
	set_var_value(mbox, "?", EXIT_SUCCESS_STR);
}
