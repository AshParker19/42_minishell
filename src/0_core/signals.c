/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/10 18:35:10 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler_heredoc(int signal)
{
	t_mbox	*mbox;

	if (signal == SIGINT)
	{
		dprintf(2, "signal handler pid (%d)\n", getpid());
		mbox = get_mbox(NULL);
		set_var_value(mbox, "?", "130");
		close(STDIN_FILENO);
		g_signal_status = SIGNAL_HEREDOC;
		mbox->stop_heredoc = ft_true;
		// dprintf(2, "CTRL C IN HEREDOC\n");
		// write(STDIN_FILENO, "\n", 1);
		// free_and_close_box_v2(mbox);
	}
}

static void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        // PRINT NEW PROMT
		g_signal_status = SIGNAL_NEW_LINE;
        write(STDIN_FILENO, "\n", 1);
        write(1, PROMT, ft_strlen(PROMT));
        rl_replace_line("", 1);
		// if in heredoc
		// amd ctrl c
    }
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
        signal(SIGINT, sig_handler_heredoc);
        signal(SIGQUIT, SIG_IGN);
    }
}
