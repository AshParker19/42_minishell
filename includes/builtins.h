/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/10/09 17:24:45 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* builtins_utils.c */
void	initialize_builtins(t_minibox *minibox);
int     check_if_builtin(t_minibox *minibox, char *cmd_name);
void    run_cmd_builtin(t_minibox *minibox, t_tree *cmd_node, int cmd_index);

void    test_builtins();
void    builtin_echo(char *txt);
void	builtin_cd(t_minibox *minibox, char *path);
void	builtin_pwd(char *args);
void    builtin_export(t_minibox *minibox, char* key_value_pair);
void    builtin_unset(t_minibox *minibox, char *key);
void    builtin_env(t_minibox *minibox, char *args);
void    builtin_exit(t_minibox *minibox, char *args);

#endif