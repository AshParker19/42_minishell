/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/10/21 12:46:18 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* bultins function pointer typedef */
typedef void	(*t_builtin_function)(t_minibox *minibox, t_tree *arg_node);

/* 
    struct for each builtit
 */
typedef struct 	s_builtin_cmd
{
    char				*cmd_name;
    t_builtin_function	func_name;
}           t_builtin_cmd;

/* builtins_utils.c */
void	initialize_builtins(t_minibox *minibox);
t_bool  is_cmd_builtin(t_minibox *minibox, char *cmd);
void    run_cmd_builtin(t_minibox *minibox, t_tree *cmd_node);
char    *strcat_args(t_tree *arg_node);

void    builtin_echo(t_minibox *minibox, t_tree *arg_node);
void	builtin_cd(t_minibox *minibox, t_tree *arg_node);
void	builtin_pwd(t_minibox *minibox, t_tree *arg_node);
void    builtin_export(t_minibox *minibox, t_tree *arg_node);
void    builtin_unset(t_minibox *minibox, t_tree *arg_node);
void    builtin_env(t_minibox *minibox, t_tree *arg_node);
void    builtin_exit(t_minibox *minibox, t_tree *arg_node);

#endif