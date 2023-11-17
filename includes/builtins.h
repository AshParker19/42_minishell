/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/11/17 22:51:54 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* bultins function pointer typedef */
typedef void	(*t_builtin_function)(t_mbox *mbox, t_ast *arg_node);

/* struct for each builtit */
typedef struct 	s_builtin_cmd
{
    char				*cmd_name;
    t_builtin_function	func_name;
}           t_builtin_cmd;

/* builtins_utils */
void	initialize_builtins(t_mbox *mbox);
t_bool  is_cmd_builtin(t_mbox *mbox, char *cmd);
void    run_cmd_builtin(t_mbox *mbox, t_ast *cmd_node);
void    save_history(t_mbox *mbox, char *inp_hist);
void    del_history(void *content);
void    free_history(t_mbox *mbox);

void    builtin_echo(t_mbox *mbox, t_ast *arg_node);
void	builtin_cd(t_mbox *mbox, t_ast *arg_node);
void	builtin_pwd(t_mbox *mbox, t_ast *arg_node);
void    builtin_export(t_mbox *mbox, t_ast *arg_node);
void    builtin_unset(t_mbox *mbox, t_ast *arg_node);
void    builtin_env(t_mbox *mbox, t_ast *arg_node);
void    builtin_exit(t_mbox *mbox, t_ast *arg_node);
void    builtin_history(t_mbox *mbox, t_ast *arg_node);

#endif