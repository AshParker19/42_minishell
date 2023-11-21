/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/21 19:17:40 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


static void	tmp_exiter(t_mbox *mbox, int *fd, char *lim, char *cur_line)
{
	if (mbox->stop_heredoc == ft_true)
		exit_heredoc_child(mbox, fd, lim, cur_line);
	check_ctrl_d(mbox, fd, lim, cur_line);	
}

static void	heredoc_child(t_mbox *mbox, int *fd, char *lim)
{
	char	*cur_line;
	t_bool	expand_vars;

	close(fd[P_RIGHT]);
	update_signals(SIGNAL_HEREDOC);
	lim = ft_strdup(lim);
	expand_vars = check_lim_qoutes(&lim);
	mbox->stop_heredoc = ft_false;
	while (FRANCENDOC_ECHOES_IN_ETERNITY)
	{
		cur_line = readline(HEREDOC_PROMPT);
		tmp_exiter(mbox, fd, lim, cur_line);
		if(cur_line[0] != '\0')
		{
			if (str_cmp_strct(cur_line, lim))
				exit_heredoc_child(mbox, fd, lim, cur_line);
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

t_bool	heredoc_parent(t_mbox *mbox, int pid_hd, int *cmd_in_fd, int *fd)
{
	int	exit_status;

	close(fd[P_LEFT]);
	waitpid(pid_hd, &exit_status, 0);
	update_signals(SIGNAL_CHILD);
	if (exit_status != EXIT_SUCCESS)
	{
		set_var_value_int(mbox, "?", exit_status);
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
t_bool	heredoc(t_mbox *mbox, t_ast *redir_node, int *cmd_in_fd)
{
	int		fd[2];
	int		exit_status;
	int		pid_hd;

	if (pipe(fd) < 0)
		return (err_free_and_close_box(mbox, EXIT_FAILURE));
	update_signals(SIGNAL_PARENT);
	pid_hd = fork();
	if (pid_hd < 0)
		return (err_free_and_close_box(mbox, EXIT_FAILURE));
	if (pid_hd == 0)
		heredoc_child(mbox, fd, redir_node->content);
	return (heredoc_parent(mbox, pid_hd, cmd_in_fd, fd));
}

	// OLD SHIT!!!	
	// if (WIFEXITED(exit_status))
	// 	exit_status = WEXITSTATUS(exit_status);
	// else if (WIFSIGNALED(exit_status))
	// {
	// 	exit_status = WTERMSIG(exit_status) + 128;
	// 	dprintf(2, "DDDDDDDDDDDDDDDDDDDDDDDDDDDD\nPID %d\n", getpid());
	// }
	// else
	// 	exit_status = 1;
			// info was written to the reaad end and will be redirected later using dup2
	// close(fd[P_RIGHT]);



	// FIX 10.11. 18:45 uncomment later maybe
	// exit_status_str = ft_itoa(exit_status);
	// set_var_value(mbox, "?", exit_status_str);
	// // dprintf(2, "{%s}{%s}\n", exit_status_str, get_var_value(mbox, "?"));
	// free(exit_status_str);