/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:32:13 by astein            #+#    #+#             */
/*   Updated: 2024/01/06 19:37:01 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H




/* builtins_utils */
void	initialize_builtins(t_mbox *mbox);
t_bool	is_cmd_builtin(t_mbox *mbox, char *cmd);
void	run_cmd_builtin(t_mbox *mbox, t_ast *cmd_node, t_bool parent);
void	save_history(t_mbox *mbox);
void	del_history_node(void *content);

#endif