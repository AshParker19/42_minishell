/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_hd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/18 19:49:45 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   The Parent Process of the hd...
 *				...closes the write end of the pipe
 *				...waits for the child process to finish
 *				...updates the exit status to the exit status of the hd child process
 *				...checks how the hd hild process was terminated:
 *					CTRL+C
 *						closes the read end of the pipe
 *						returns false
 *					EOF or limitter
 *						returns true
 *
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#heredoc
 * 
 * @param   mbox        
 * @param   pid_hd      
 * @param   cmd_in_fd   
 * @param   fd          
 * @return  t_bool      
 */
static t_bool	hd_parent(t_mbox *mbox, int pid_hd, int *cmd_in_fd, int *fd)
{
	int	exit_status;

	exit_status = 0;
	close(fd[P_LEFT]);
	conf_sig_handler(SIG_STATE_IGNORE);
	waitpid(pid_hd, &exit_status, 0);
	conf_sig_handler(SIG_STATE_CHILD);
	if (exit_status != EXIT_SUCCESS)
	{
		g_signal_status = SIGNAL_EXIT_HD;
		set_var_value_int(mbox, "?", WEXITSTATUS(exit_status));
		close (fd[P_RIGHT]);
		return (ft_false);
	}
	else
	{
		set_var_value_int(mbox, "?", EXIT_SUCCESS);
		*cmd_in_fd = fd[P_RIGHT];
		return (ft_true);
	}
}

/**
 * @brief   This function manages the heredoc redirection
 * 
 * DOCUMENATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#heredoc
 * 
 * @param   mbox        
 * @param   redir_node  
 * @param   cur_p       
 * @return  t_bool      
 */
t_bool	setup_hd(t_mbox *mbox, t_ast *redir_node, int *cur_p)
{
	int		fd[2];
	int		pid_hd;

	if (pipe(fd) < 0)
		return (destroy_mbox_with_exit(mbox, EXIT_FAILURE));
	pid_hd = fork();
	if (pid_hd < 0)
		return (destroy_mbox_with_exit(mbox, EXIT_FAILURE));
	if (pid_hd == 0)
		hd_child(mbox, (t_hd){fd, ft_strdup(redir_node->content), NULL}, cur_p);
	return (hd_parent(mbox, pid_hd, &mbox->exec.io.cmd_fd[CMD_IN], fd));
}
