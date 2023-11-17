/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:45:50 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/17 17:35:03 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    save_history(t_mbox *mbox, char *inp_hist)
{
    t_history   *cur;
    t_history   *new_inp;
    static int  i;

    new_inp = ft_calloc(1, sizeof(t_history));
    if (!new_inp)
        return ;
    new_inp->inp_hist = ft_strdup(inp_hist);
    new_inp->inp_count = ++i;
    if (!mbox->history)
        mbox->history = new_inp;
    else
    {
        cur = mbox->history;
        while (cur->next)
            cur = cur->next;
        cur->next = new_inp;    
    }    
}

void    builtin_history(t_mbox *mbox, t_ast *arg_node)
{
    t_history   *cur;
	char		*count;

    (void)arg_node;
    cur = mbox->history;
    while (cur)
    {
		ft_putstr_fd("  ", mbox->executor.io.cmd_fd[CMD_OUT]);
		count = ft_itoa(cur->inp_count);
		ft_putstr_fd(count, mbox->executor.io.cmd_fd[CMD_OUT]);
		free (count);
		ft_putstr_fd("  ", mbox->executor.io.cmd_fd[CMD_OUT]);
		ft_putendl_fd(cur->inp_hist, mbox->executor.io.cmd_fd[CMD_OUT]);
        cur = cur->next;
    }
	set_var_value(mbox, "?", EXIT_SUCCESS_STR);
}

void    free_history(t_mbox *mbox)
{
    t_history   *cur;
    t_history   *temp;

    cur = mbox->history;
    while (cur)
    {
        temp = cur;
        cur = cur->next;
        if (temp)
        {
            free(temp->inp_hist);
            free(temp);
        }
    }
    mbox->history = NULL;
}
