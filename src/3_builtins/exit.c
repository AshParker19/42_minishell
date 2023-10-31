/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:57 by astein            #+#    #+#             */
/*   Updated: 2023/10/31 17:05:19 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// TODO: check signal 

/**
 * @brief   exits the current process via 'free_and_close_box'
 *          if there is an 'arg_node' prints an error instead
 * 
 * @param   mbox 
 * @param   arg_node 
 */
void    builtin_exit(t_mbox *mbox, t_ast *arg_node)
{
    if (arg_node && !ft_str_is_numeric(arg_node->content))
        create_error_msg("nnnn", ERR_PROMT, "exit: ", arg_node->content,  
            ": numeric argument required");
    else
    {
        ft_putstr_fd("exit\n", STDOUT_FILENO);
        free_and_close_box_v2(mbox);
    }
}
