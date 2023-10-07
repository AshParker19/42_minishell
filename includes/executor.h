/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:55:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/07 15:10:30 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/******************************************************************************/
typedef struct s_exec
{
    char    **path_dirs;
    char    **cmd_builtins;
    char    **cmd_av;
    int     fd[2];
    int     dup_fd[2];
    int     prev_fd;
    int     exit_status;
}   t_exec;

enum e_cmd_type
{
    CMD,
    CMD_PIPE,
    PIPE_CMD,
    PIPE_CMD_PIPE
};

enum e_pipe_end
{
    READ_END,
    WRITE_END
};

/******************************************************************************/
/* executor */
void    execute(t_minibox *minibox);
void    single_cmd(t_minibox *minibox, t_tree *cmd_node, char *cmd);

/* executor_utils */
void    load_executor(t_minibox *minibox);
void	initialize_executor(t_minibox *minibox);
void	print_executor_output(t_minibox *minibox, int i); //TODO: remove at the end
void    free_executor(t_minibox *minibox);
char    *find_cmd(t_minibox *minibox, char *cmd, int i);
char	*ft_strjoin_slash(char *src, char *dest);
void    get_cmd_av(t_minibox *minibox, t_tree *root);
void	free_process(t_minibox *minibox);

#endif