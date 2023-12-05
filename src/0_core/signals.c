/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/05 16:59:36 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_print(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (signal == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}

static void	sh_hd(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
		g_signal_status = SIGNAL_EXIT_HD;
	}
}

/**
 * @brief	in main loop just print a new promt in a new line
 * 
 * 			TODO: EXIT CODE?
 * 
 * @param 	signal 
 */
static void	sh_main(int signal)
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

static void	update_signals_child(int sig_state)
{
	if (sig_state == SIG_STATE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (sig_state == SIG_STATE_CHILD_BUILTIN)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_IGN);	
	}
	else if (sig_state == SIG_STATE_HD_CHILD)
	{
		signal(SIGINT, sh_hd);
		signal(SIGQUIT, SIG_IGN);
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
		signal(SIGINT, sh_main);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_PARENT)
	{
		signal(SIGINT, sh_print);
		signal(SIGQUIT, sh_print);
	}
	else if (sig_state == SIG_STATE_IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		update_signals_child(sig_state);

		

}
