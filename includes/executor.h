/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:55:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/17 20:35:38 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/******************************************************************************/
typedef struct s_io
{
    t_bool  use_pipe[2];
    // t_tree  *redir;
    int     cmd_fd[2];
    int     dup_fd[2];
    int     prev_pipe[2];
}   t_io;

typedef struct s_exec
{
    char    **path_dirs;
    char    **cmd_builtins;
    char    **cmd_av;
    t_io    io;
    int     pid;    //FIXME:
    int     exit_status;
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
void    execute(t_minibox *minibox);
void    single_cmd(t_minibox *minibox, t_tree *cmd_node, char *cmd);
void    run_cmd_system(t_minibox *minibox, t_tree *cmd_node);

/* pipes */
void    setup_use_pipe(t_minibox *minibox, int status);
void    setup_pipes(t_minibox *minibox);


/* redirections */
void    handle_redir(t_tree *node, int *in_fd, int *out_fd);
void    setup_redir(t_minibox *minibox, t_tree *redir_node);

/* heredoc */
void    heredoc(t_tree *redir_node, int *in_fd, char *line);

/* executor_utils */
void    load_executor(t_minibox *minibox);
void	initialize_io(t_minibox *minibox);
void	print_executor_output(t_minibox *minibox, int i); //TODO: remove at the end
void    free_executor(t_minibox *minibox);
int		cmd_counter(t_tree *tree_node);
// char    *get_cmd_path(t_minibox *minibox, char *cmd, int i);
void    get_cmd_av(t_minibox *minibox, t_tree *root);
void	free_process(t_minibox *minibox);

#endif