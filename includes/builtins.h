/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/10/13 23:03:10 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* builtins_utils.c */
void	initialize_builtins(t_minibox *minibox);
int     check_if_builtin(t_minibox *minibox, char *cmd_name);
void    run_cmd_builtin(t_minibox *minibox, t_tree *cmd_node, int cmd_index);
char    *strcat_args(t_tree *arg_node);

void    test_builtins();
void    builtin_echo(t_minibox *minibox, t_tree *arg_node);
void	builtin_cd(t_minibox *minibox, t_tree *arg_node);
void	builtin_pwd(t_minibox *minibox, t_tree *arg_node);
void    builtin_export(t_minibox *minibox, t_tree *arg_node);
void    builtin_unset(t_minibox *minibox, t_tree *arg_node);
void    builtin_env(t_minibox *minibox, t_tree *arg_node);
void    builtin_exit(t_minibox *minibox, t_tree *arg_node);

#endif