/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:55:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/06 19:35:48 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_exec
{
    char    **path_dirs;
    char    **cmd_builtins;
    // int     fd[2];
    // int     dup_fd[2];
    // int     p_fd;
}   t_exec;


/* executor.c */
void    execute(t_minibox *minibox);

/* executor_utils.c */
void    load_executor(t_minibox *minibox);
void	print_executor_output(t_minibox *minibox, int i);
void    free_executor(t_minibox *minibox);

#endif