/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:56 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/19 02:09:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief   This file handles all the signals that are used in the project.
 * 			Each time a fork is happening all existing processes will be set to
 * 			a specific 'signal status' via 'conf_sig_handler'. This status will
 * 			be used to determine which signal handling should be used in the
 * 			calling process.
 * 
 * 		SIGNALS:
 * 			CTRL + C  =   SIGINT
 * 			CTRL + \  =   SIGQUIT
 * 			CTRL + D  =   EOF
 * 
 * 		DOCUMENTATION:
 *		https://github.com/ahokcool/frankenshell/docs/documentation.md#signals
 * 
 */

#include "frankenshell.h"

/**
 * @brief   Handling the 'CTRL + \' (SIGQUIT) in the parent process
 * 
 * 			NOTE: The child will have the state SIG_STATE_CHILD and therefore
 * 					perform the default action (terminating the process)
 * 
 * @param   signal      
 */
static void	sh_parent(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (signal == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * @brief   Handling the 'CTRL + C' (SIGINT) in the heredoc child process
 * 			The herdoc process will be stuck in a loop until the user enters
 * 			the limiter or presses CTRL + D. In both cases the process will be
 * 			terminated. To exit this loop when receiving SIGINT we need to
 * 			close the STDIN_FILENO.
 * 
 * 			Also the global variable 'g_signal_status' will be set to control
 * 			the behaviour of the further execution.
 * 
 * @param   signal      
 */
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
 * @brief   The main frankenshell process will be stuck in a loop until the user
 * 			exits the program. In this loop the user can enter commands and
 * 			press CTRL + C (SIGINT) to get a new prompt.
 * 			Therfore the readline char buffer will be cleared and a new line
 * 			will be printed.
 * 
 * 			The flag 'g_signal_status' will be set to notice the main loop to
 * 			set the exit status to 130 (like bash does).
 * 
 * @param   signal      
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

/**
 * @brief   Whenever we fork we need to adjust the signal handling in both
 * 			processes. This function updates the signal handling of the calling
 * 			process to the given 'sig_state'.
 * 	
 * 			NOTE: the enum 'e_signal_state' is defined in 'icludes/config.h'
 * 
 * @param   sig_state   
 */
void	conf_sig_handler(int sig_state)
{
	if (sig_state == SIG_STATE_MAIN)
	{
		signal(SIGINT, sh_main);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_PARENT)
	{
		signal(SIGINT, sh_parent);
		signal(SIGQUIT, sh_parent);
	}
	else if (sig_state == SIG_STATE_IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_state == SIG_STATE_CHILD)
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
