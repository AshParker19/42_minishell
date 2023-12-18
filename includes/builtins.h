/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/12/18 01:54:31 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* bultins function pointer typedef */
typedef void	(*t_builtin_function)(t_mbox *mbox, t_ast *arg_node);

/* struct for each builtin */
typedef struct s_builtin_cmd
{
	char				*cmd_name;
	t_builtin_function	func_name;
}						t_builtin_cmd;

/* bultin functions */
void	builtin_echo(t_mbox *mbox, t_ast *arg_node);
void	builtin_cd(t_mbox *mbox, t_ast *arg_node);
void	builtin_pwd(t_mbox *mbox, t_ast *arg_node);
void	builtin_export(t_mbox *mbox, t_ast *arg_node);
void	builtin_unset(t_mbox *mbox, t_ast *arg_node);
void	builtin_env(t_mbox *mbox, t_ast *arg_node);
void	builtin_exit(t_mbox *mbox, t_ast *arg_node);
void	builtin_history(t_mbox *mbox, t_ast *arg_node);
void	builtin_header(t_mbox *mbox, t_ast *arg_node);
void	builtin_infomode(t_mbox *mbox, t_ast *arg_node);

/* builtins_utils */
void	initialize_builtins(t_mbox *mbox);
t_bool	is_cmd_builtin(t_mbox *mbox, char *cmd);
void	run_cmd_builtin(t_mbox *mbox, t_ast *cmd_node, t_bool parent);
void	save_history(t_mbox *mbox);
void	del_history_node(void *content);
void	case_equal_sign(t_mbox *mbox, t_ast *arg_node, t_bool *fnd_err,
			char *equal_sign);
void	case_no_equal_sign(t_mbox *mbox, t_ast *arg_node, t_bool *fnd_err);

#endif