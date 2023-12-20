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

/*********************************# FUNCTIONS #********************************/

/* exec */
void	execute_ast(t_mbox *mbox);
void	run_cmd_system(t_mbox *mbox, t_ast *cmd_node);

/* cmd runner */
void	run_cmd_main(t_mbox *mbox, t_ast *cmd_node);
t_bool	run_single_builtin(t_mbox *mbox);

/* pipes */
void	setup_use_pipe(t_mbox *mbox, int status);
void	setup_pipes(t_mbox *mbox, int *cur_pipe);
void	setup_process_std_tmp(t_mbox *mbox);

/* redirections */
t_bool	setup_redirs(t_mbox *mbox, t_ast *redir_node, int *cur_p);

/* heredoc */
t_bool	setup_hd(t_mbox *mbox, t_ast *redir_node, int *cur_p);

/* executor_utils */
void	initialize_io(t_mbox *mbox, t_ast *cur, int cmd_pos);
int		cmd_counter(t_ast *ast_node);
char	**get_args_to_matrix(t_mbox *mbox, char *cmd, t_ast *arg_node);
void	close_process_fds_v2(t_mbox *mbox);
t_bool	allocate_pid_array(t_mbox *mbox);
t_bool	hd_parent_wait(t_mbox *mbox, int *cur_p, t_ast *node_cpy,
			int kid_pid);

char	*get_abs_cmd_path(t_mbox *mbox, char *cmd);
void	free_process_v2(t_mbox *mbox);

#endif