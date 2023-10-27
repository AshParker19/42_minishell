/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/10/27 15:13:06 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* bultins function pointer typedef */
typedef void	(*t_builtin_function)(t_mbox *mbox, t_tree *arg_node);

/* 
    struct for each builtit
 */
typedef struct 	s_builtin_cmd
{
    char				*cmd_name;
    t_builtin_function	func_name;
}           t_builtin_cmd;

/* builtins_utils.c */
void	initialize_builtins(t_mbox *mbox);
t_bool  is_cmd_builtin(t_mbox *mbox, char *cmd);
void    run_cmd_builtin(t_mbox *mbox, t_tree *cmd_node);
char    *strcat_args(t_tree *arg_node);

void    builtin_echo(t_mbox *mbox, t_tree *arg_node);
void	builtin_cd(t_mbox *mbox, t_tree *arg_node);
void	builtin_pwd(t_mbox *mbox, t_tree *arg_node);
void    builtin_export(t_mbox *mbox, t_tree *arg_node);
void    builtin_unset(t_mbox *mbox, t_tree *arg_node);
void    builtin_env(t_mbox *mbox, t_tree *arg_node);
void    builtin_exit(t_mbox *mbox, t_tree *arg_node);

#endif