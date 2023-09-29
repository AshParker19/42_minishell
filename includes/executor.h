/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:55:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/29 18:19:41 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

// BUILTINS
// TODO:
// Alex will put all the buildin prototypes here...

void    test_builtins();
void	builtin_cd(t_minibox *minibox, char *path);
void    bultin_echo(char *txt);
void    bultin_env(t_minibox *minibox);
void    bultin_exit(void);
void    bultin_export(t_minibox *minibox, char* key_value_pair);
void    bultin_unset(t_minibox *minibox, char* key);
void	builtin_pwd(void);

#endif