/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/31 21:17:42 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        // PRINT NEW PROMT
        write(STDIN_FILENO, "\n", 1);
        write(1, PROMT, ft_strlen(PROMT));
        rl_replace_line("", 1);
    }
    else if (signal == SIGQUIT)
        dprintf(2, "asd\n");
        // builtin_exit(mbox, NULL);
}

/**
 * @brief   Whenever we fork we need to adjust the signal handling in the 
 *          child and parent. This can be done with this function using the
 *          following codes:
 *  
 *          SIGNAL_MAIN     showing basic promt
 *          SIGNAL_PARENT   ignore all signals
 *          SIGNAl_CHILD    basic setup for child
 *          SIGNAL_HEREDOC  for heredoc
 * 
 *          NOTE:
 *              CTRL C  =   SIGINT
 *              CTRL \  =   SIGQUIT
 *              CTRL D  =   EOF
 * 
 * @param sig_state 
 */
void update_signals(int sig_state)
{
    if (sig_state == SIGNAL_MAIN)
    {
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (sig_state == SIGNAL_PARENT)
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
    }
    else if (sig_state == SIGNAL_CHILD)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
    }
    else if (sig_state == SIGNAL_HEREDOC)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_IGN);
    }
}
