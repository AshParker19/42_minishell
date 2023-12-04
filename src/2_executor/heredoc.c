/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/04 18:47:15 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tmp_exiter(t_mbox *mbox, int *fd, char *lim, char *cur_line)
{
	if (g_signal_status == SIGNAL_EXIT_HD)
		exit_heredoc_child(mbox, fd, lim, cur_line, 130);
	check_ctrl_d(mbox, fd, lim, cur_line);
}

static void	hd_child(t_mbox *mbox, int *fd, char *lim, int *cur_p)
{
	char	*cur_line;
	t_bool	expand_vars;

	close(fd[P_RIGHT]);
	if (cur_p && cur_p[P_RIGHT] != -1)
		close(cur_p[P_RIGHT]);
	update_signals(SIG_STATE_HD_CHILD);
	lim = ft_strdup(lim);
	expand_vars = check_lim_qoutes(&lim);
	while (FRANCENDOC_ECHOES_IN_ETERNITY)
	{
		cur_line = readline(HEREDOC_PROMPT);
		tmp_exiter(mbox, fd, lim, cur_line);
		if (cur_line[0] != '\0')
		{
			if (str_cmp_strct(cur_line, lim))
				exit_heredoc_child(mbox, fd, lim, cur_line, 0);
			if (expand_vars && cur_line)
				cur_line = expand_heredoc_input(mbox, cur_line);
			ft_putendl_fd(cur_line, fd[P_LEFT]);
		}
		else
			ft_putendl_fd("", fd[P_LEFT]);
		if (cur_line)
			free(cur_line);
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
		hd_child(mbox, fd, redir_node->content, cur_p);
	return (hd_parent(mbox, pid_hd, &mbox->executor.io.cmd_fd[CMD_IN], fd));
}
