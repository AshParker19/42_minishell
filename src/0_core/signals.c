/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/01 15:26:10 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler_heredoc(int signal)
{
	t_mbox	*mbox;

	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		mbox = get_mbox(NULL);
		set_var_value(mbox, "?", "130");
		close(STDIN_FILENO);
		g_signal_status = SIGNAL_HEREDOC;
		mbox->stop_heredoc = ft_true;
	}
}

/**
 * @brief	in main loop just print a new promt in a new line
 * 
 * 			TODO: EXIT CODE?
 * 
 * @param 	signal 
 */
static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal_status = SIGNAL_NEW_LINE;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
void	update_signals(int sig_state)
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
