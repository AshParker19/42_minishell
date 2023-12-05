/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/05 13:41:12 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	this function will be only called by 'heredoc' for each line
 * 			checks
 * 			1. if interrupted by CTRL C
 *			2, if interrupted by CTRL D
 * 
 * @param mbox 
 * @param hd 
 */
static void	tmp_exiter(t_mbox *mbox, t_hd *hd)
{
	if (g_signal_status == SIGNAL_EXIT_HD)
		exit_heredoc_child(mbox, hd, 130);
	if (!hd->cur_line)
	{
		err_msg(mbox, NO_EXIT_STATUS, "nnynnn", ERR_P,
			W_HD, ft_itoa(mbox->count_cycles), DW, hd->lim, "')");
		exit_heredoc_child(mbox, hd, EXIT_SUCCESS);
	}
}

static void	hd_child(t_mbox *mbox, t_hd hd, int *cur_p)
{
	t_bool	expand_vars;
	
	close(hd.fd[P_RIGHT]);
	if (cur_p && cur_p[P_RIGHT] != -1)
		close(cur_p[P_RIGHT]);
	update_signals(SIG_STATE_HD_CHILD);
	expand_vars = check_lim_qoutes(&hd.lim);
	while (FRANCENDOC_ECHOES_IN_ETERNITY)
	{
		hd.cur_line = readline(HEREDOC_PROMPT);
		tmp_exiter(mbox, &hd);
		if (hd.cur_line[0] != '\0')
		{
			if (str_cmp_strct(hd.cur_line, hd.lim))
				exit_heredoc_child(mbox, &hd, 0);
			if (expand_vars && hd.cur_line)
				hd.cur_line = expand_heredoc_input(mbox, hd.cur_line);
			ft_putendl_fd(hd.cur_line, hd.fd[P_LEFT]);
		}
		else
			ft_putendl_fd("", hd.fd[P_LEFT]);
		if (hd.cur_line)
			free(hd.cur_line);
	}
}

t_bool	hd_parent(t_mbox *mbox, int pid_hd, int *cmd_in_fd, int *fd)
{
	int	exit_status;

	exit_status = 0;
	close(fd[P_LEFT]);
	update_signals(SIG_STATE_IGNORE);
	waitpid(pid_hd, &exit_status, 0);
	update_signals(SIG_STATE_CHILD);
	if (exit_status != EXIT_SUCCESS)
	{
		g_signal_status = SIGNAL_EXIT_HD;
		set_var_value_int(mbox, "?", WEXITSTATUS(exit_status));
		close (fd[P_RIGHT]);
		return (ft_false);
	}
	else
	{
		*cmd_in_fd = fd[P_RIGHT];
		return (ft_true);
	}
}

/**
 * @brief 
 * 
 * 			NOTE: if the var expansion turns out to be excatlly the lim str
 * 					it still doesnt exit the heredoc
 * 				e.g. << -R cat
 * 					   > asd
 * 					   > $LESS (this expands to -R but doens't exit the heredoc)
 * 					   > -R
 * 
 * @param mbox 
 * @param redir_node 
 * @param cmd_in_fd 
 * @return t_bool 
 */
t_bool	heredoc(t_mbox *mbox, t_ast *redir_node, int *cur_p)
{
	int		fd[2];
	int		pid_hd;

	if (pipe(fd) < 0)
		return (err_free_and_close_box(mbox, EXIT_FAILURE));
	pid_hd = fork();
	if (pid_hd < 0)
		return (err_free_and_close_box(mbox, EXIT_FAILURE));
	if (pid_hd == 0)
		hd_child(mbox,(t_hd){fd, ft_strdup(redir_node->content), NULL} ,cur_p);
	return (hd_parent(mbox, pid_hd, &mbox->executor.io.cmd_fd[CMD_IN], fd));
}
