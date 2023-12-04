/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:55:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/04 14:44:30 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_io
{
	t_bool  use_pipe[2];
	int     cmd_fd[2];
	int     dup_fd[2];
	int     prev_pipe[2];
}   t_io;

typedef struct s_exec
{
	t_builtin_cmd   builtins[10];
	t_io            io;
	int             *pid;
	int             pid_index;
}   t_exec;


/******************************************************************************/
/* executor */
void	execute(t_mbox *mbox);
void    run_cmd_system(t_mbox *mbox, t_ast *cmd_node);

/* cmd runner */
void    run_cmd_main(t_mbox *mbox, t_ast *cmd_node);
t_bool  run_single_builtin(t_mbox *mbox);


/* pipes */
void    setup_use_pipe(t_mbox *mbox, int status);
void    setup_pipes(t_mbox *mbox, int *cur_pipe);
void    setup_process_std(t_mbox *mbox);

/* redirections */
t_bool	configure_redir(t_mbox *mbox, t_ast *redir_node, int *cur_p);

/* heredoc */
t_mbox	*get_mbox(t_mbox *mbox);
t_bool	heredoc(t_mbox *mbox, t_ast *redir_node, int *cur_p);
char    *get_key(char *str, int *i);
// void	exit_heredoc_child(t_mbox *mbox, int *fd, char *lim, char *line);
void	exit_heredoc_child(t_mbox *mbox, int *fd, char *lim, char *line, int exit_status);
void 	check_ctrl_d(t_mbox *mbox, int *fd, char *lim, char *line);
t_bool	check_lim_qoutes(char **str);
char	*expand_heredoc_input(t_mbox *mbox, char *str);

/* executor_utils */
void	initialize_io(t_mbox *mbox);
int		cmd_counter(t_ast *ast_node);
char 	**args_to_matrix(t_mbox *mbox, char *cmd, t_ast *arg_node);
void	close_process_fds_v2(t_mbox *mbox);
t_bool	allocate_pid_array(t_mbox *mbox);

char    *get_abs_cmd_path(t_mbox *mbox, char *cmd);
void	free_process_v2(t_mbox *mbox);
#endif