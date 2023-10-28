/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:55:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/27 23:57:53 by astein           ###   ########.fr       */
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
    // TODO: REMOVE THE VARS THAT ARE ONLY FOR ONE CYCLE!!!
    char            **path_dirs;
    t_builtin_cmd   builtins[8];
    char            **cmd_av;
    t_io            io;
    int             *pid;
    int             pid_index;
    // int             exit_status;
}   t_exec;


enum e_cmd_type
{
    SINGLE_CMD,
    FIRST_CMD,
    MIDDLE_CMD,
    LAST_CMD
};

enum e_cmd_dir
{
    CMD_IN,       //    stdin 0    std out 1
    CMD_OUT
};

enum e_pipe_side
{
    P_RIGHT,  //     1 in   ->     0 out
    P_LEFT
};

/******************************************************************************/
/* executor */
t_bool  execute(t_mbox *mbox);
void    run_cmd_system(t_mbox *mbox, t_tree *cmd_node);

/* pipes */
void    setup_use_pipe(t_mbox *mbox, int status);
void    setup_pipes(t_mbox *mbox, int *cur_pipe);
void    setup_process_std(t_mbox *mbox);

/* redirections */
t_bool    setup_redir(t_mbox *mbox, t_tree *redir_node);

/* heredoc */
int    heredoc(t_mbox *mbox, t_tree *redir_node, int *cmd_in_fd);

/* executor_utils */
void    load_executor(t_mbox *mbox);
void	initialize_io(t_mbox *mbox);
void	print_executor_output(t_mbox *mbox, int i); //TODO: remove at the end
void    free_executor(t_mbox *mbox);
int		cmd_counter(t_tree *tree_node);
// char    *get_cmd_path(t_mbox *mbox, char *cmd, int i);
void    get_cmd_av(t_mbox *mbox, t_tree *root);
void	free_process(t_mbox *mbox);
void    reset_executor(t_mbox *mbox);

#endif