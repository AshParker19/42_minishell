/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:55:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/15 01:52:34 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/*****************************# DATA STRUCTURES #******************************/

/* data for input/output manipulations */
typedef struct s_io
{
	t_bool	use_pipe[2];
	int		cmd_fd[2];
	int		dup_fd[2];
	int		prev_pipe[2];
}	t_io;

/*  data for execution */
typedef struct s_exec
{
	t_builtin_cmd	builtins[10];
	t_io			io;
	int				*pid;
	int				pid_index;
}	t_exec;

/* heredoc */
typedef struct s_hd
{
	int				*fd;
	char			*lim;
	char			*cur_line;
}	t_hd;

/*********************************# FUNCTIONS #********************************/

/* exec */
void	execute(t_mbox *mbox);
void	run_cmd_system(t_mbox *mbox, t_ast *cmd_node);

/* cmd runner */
void	run_cmd_main(t_mbox *mbox, t_ast *cmd_node);
t_bool	run_single_builtin(t_mbox *mbox);

/* pipes */
void	setup_use_pipe(t_mbox *mbox, int status);
void	setup_pipes(t_mbox *mbox, int *cur_pipe);
void	setup_process_std_tmp(t_mbox *mbox);

/* redirections */
t_bool	configure_redir(t_mbox *mbox, t_ast *redir_node, int *cur_p);

/* heredoc */
t_bool	heredoc(t_mbox *mbox, t_ast *redir_node, int *cur_p);
char	*get_key(char *str, int *i);
void	exit_heredoc_child(t_mbox *mbox, t_hd *hd, int exit_status);
t_bool	check_lim_qoutes(char **str);
char	*expand_heredoc_input(t_mbox *mbox, char *str);

/* executor_utils */
void	initialize_io(t_mbox *mbox, t_ast *cur, int cmd_pos);
int		cmd_counter(t_ast *ast_node);
char	**args_to_matrix(t_mbox *mbox, char *cmd, t_ast *arg_node);
void	close_process_fds_v2(t_mbox *mbox);
t_bool	allocate_pid_array(t_mbox *mbox);
t_bool	hd_parent_wait(t_mbox *mbox, int *cur_p, t_ast *node_cpy,
			int kid_pid);

char	*get_abs_cmd_path(t_mbox *mbox, char *cmd);
void	free_process_v2(t_mbox *mbox);

#endif