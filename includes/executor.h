/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:55:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/11 11:03:30 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/******************************************************************************/
typedef struct s_io
{
    t_bool  use_pipe[2];
    t_tree  *redir;
    int     fd[2];
    int     dup_fd[2];
    int     prev_fd;
}   t_io;

typedef struct s_exec
{
    char    **path_dirs;
    char    **cmd_builtins;
    char    **cmd_av;
    t_io    io;
    int     pid1;
    int     pid2;
    int     exit_status;
}   t_exec;


enum e_cmd_type
{
    SINGLE_CMD,
    FIRST_CMD,
    MIDDLE_CMD,
    LAST_CMD
};

enum e_pipe_end
{
    READ_END,  //     1 in   ->     0 out
    WRITE_END
};

/******************************************************************************/
/* executor */
void    execute(t_minibox *minibox);
void    single_cmd(t_minibox *minibox, t_tree *cmd_node, char *cmd);
void    run_cmd_system(t_minibox *minibox, t_tree *cmd_node);

/* pipes */
void    setup_use_pipe(t_minibox *minibox, int status);


/* redirections */
void    handle_redir(t_tree *node, int *in_fd, int *out_fd);
void    setup_redir(t_minibox *minibox);

/* executor_utils */
void    load_executor(t_minibox *minibox);
void	initialize_io(t_minibox *minibox);
void	print_executor_output(t_minibox *minibox, int i); //TODO: remove at the end
void    free_executor(t_minibox *minibox);
// char    *get_cmd_path(t_minibox *minibox, char *cmd, int i);
void    get_cmd_av(t_minibox *minibox, t_tree *root);
void	free_process(t_minibox *minibox);

#endif