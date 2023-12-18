/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:54:41 by astein            #+#    #+#             */
/*   Updated: 2023/12/18 01:54:08 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   initialize the array of 't_builtin_cmd' aka function pointers and
 *          function name
 * 
 *          NOTE: only called once by 'main' on startup
 * 
 * @param mbox 
 */
void	initialize_builtins(t_mbox *mbox)
{
	mbox->exec.builtins[0].cmd_name = "echo";
	mbox->exec.builtins[0].func_name = builtin_echo;
	mbox->exec.builtins[1].cmd_name = "cd";
	mbox->exec.builtins[1].func_name = builtin_cd;
	mbox->exec.builtins[2].cmd_name = "pwd";
	mbox->exec.builtins[2].func_name = builtin_pwd;
	mbox->exec.builtins[3].cmd_name = "export";
	mbox->exec.builtins[3].func_name = builtin_export;
	mbox->exec.builtins[4].cmd_name = "unset";
	mbox->exec.builtins[4].func_name = builtin_unset;
	mbox->exec.builtins[5].cmd_name = "env";
	mbox->exec.builtins[5].func_name = builtin_env;
	mbox->exec.builtins[6].cmd_name = "exit";
	mbox->exec.builtins[6].func_name = builtin_exit;
	mbox->exec.builtins[7].cmd_name = "history";
	mbox->exec.builtins[7].func_name = builtin_history;
	mbox->exec.builtins[8].cmd_name = "42";
	mbox->exec.builtins[8].func_name = builtin_header;
	mbox->exec.builtins[9].cmd_name = "infomode";
	mbox->exec.builtins[9].func_name = builtin_infomode;
	mbox->exec.builtins[10].cmd_name = NULL;
	mbox->exec.builtins[10].func_name = NULL;
}

/**
 * @brief   traverses through the ll and checks if an accepted string 
 *          is one of the builtin commands
 *          returns corresponding boolean value
 * 
 * @param   mbox 
 * @param   cmd 
 * @return  t_bool 
 */
t_bool	is_cmd_builtin(t_mbox *mbox, char *cmd)
{
	int	i;

	i = -1;
	while (mbox->exec.builtins[++i].cmd_name)
	{
		if (str_cmp_strct(mbox->exec.builtins[i].cmd_name, cmd))
			return (ft_true);
	}
	return (ft_false);
}
