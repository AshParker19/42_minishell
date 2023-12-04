/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/04 15:25:11 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler_print(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (signal == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}


static void	sig_handler_heredoc(int signal)
{
	t_mbox	*mbox;

	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		mbox = get_mbox(NULL);
		set_var_value(mbox, "?", "130");
		close(STDIN_FILENO);
		g_signal_status = SIGNAL_EXIT_HD;
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
 *          SIG_STATE_MAIN     showing basic promt
 *          SIG_STATE_PARENT   ignore all signals
 *          SIGNAl_CHILD    basic setup for child
 *          SIG_STATE_HD_CHILD  for heredoc
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
	if (sig_state == SIG_STATE_MAIN)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_PARENT)
	{
		signal(SIGINT, sig_handler_print);
		signal(SIGQUIT, sig_handler_print);
	}
	else if (sig_state == SIG_STATE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (sig_state == SIG_STATE_HD_CHILD)
	{
		signal(SIGINT, sig_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_HD_PARENT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
