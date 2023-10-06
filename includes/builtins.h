/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/10/06 19:21:16 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* builtins_utils.c */
void	initialize_builtins(t_minibox *minibox);
int    check_if_builtin(t_minibox *minibox, char *cmd_name);
void    run_builtin(t_tree *cmd_node, int builtin_cmd_index);

void    test_builtins();
void	builtin_cd(t_minibox *minibox, char *path);
void    bultin_echo(char *txt);
void    bultin_env(t_minibox *minibox);
void    bultin_exit(void);
void    bultin_export(t_minibox *minibox, char* key_value_pair);
void    bultin_unset(t_minibox *minibox, char* key);
void	builtin_pwd(void);
#endif