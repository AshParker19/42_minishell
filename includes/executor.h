/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:55:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/10 17:08:02 by astein           ###   ########.fr       */
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
    t_builtin_cmd   builtins[9];
    char            **cmd_av;
    t_io            io;
    int             *pid;
    int             pid_index;
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
void    run_cmd_system(t_mbox *mbox, t_ast *cmd_node);

/* cmd runner */
void    run_cmd_main(t_mbox *mbox, t_ast *cmd_node);
t_bool  run_single_builtin(t_mbox *mbox);


/* pipes */
void    setup_use_pipe(t_mbox *mbox, int status);
void    setup_pipes(t_mbox *mbox, int *cur_pipe);
void    setup_process_std(t_mbox *mbox);

/* redirections */
t_bool    configure_redir(t_mbox *mbox, t_ast *redir_node);

/* heredoc */
t_mbox	*get_mbox(t_mbox *mbox);
void    heredoc(t_mbox *mbox, t_ast *redir_node, int *cmd_in_fd);
char    *get_key(char *str, int *i);

/* executor_utils */
void	initialize_io(t_mbox *mbox);
int		cmd_counter(t_ast *ast_node);
void    get_cmd_av(t_mbox *mbox, t_ast *root);
void	close_process_fds_v2(t_mbox *mbox);

char    *get_cmd_path(t_mbox *mbox, char *cmd, int i, t_bool abs);
void	free_process_v2(t_mbox *mbox);
#endif