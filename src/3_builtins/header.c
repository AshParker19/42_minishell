/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:00:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/15 14:08:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	just prints a pretty 42 logo
 * 
 * @param	mbox 
 * @param	arg_node 
 */
void	builtin_header(t_mbox *mbox, t_ast *arg_node)
{
	(void)arg_node;
	ft_putstr_fd(CYAN"       444444444   "YELLOW"222222222222222    \n"\
	CYAN"      4"B_WHITE"::::::::"CYAN"4  "YELLOW"2"B_WHITE":::::::::::::::"\
	YELLOW"22  \n"CYAN"     4"B_WHITE":::::::::"CYAN"4  "YELLOW"2"B_WHITE \
	"::::::"YELLOW"222222"B_WHITE":::::"YELLOW"2 \n"CYAN"    4"B_WHITE"::::"\
	CYAN"44"B_WHITE"::::"CYAN"4  "YELLOW"2222222     2"B_WHITE":::::"YELLOW \
	"2 \n"CYAN"   4"B_WHITE"::::"CYAN"4 4"B_WHITE"::::"CYAN"4              " \
	YELLOW"2" B_WHITE":::::"YELLOW"2 \n"CYAN"  4"B_WHITE"::::"CYAN"4  4" \
	B_WHITE"::::"CYAN"4              "YELLOW"2"B_WHITE":::::"YELLOW"2 \n"CYAN \
	" 4"B_WHITE"::::"CYAN"4   4"B_WHITE"::::"CYAN"4           "YELLOW"2222"\
	B_WHITE"::::" YELLOW"2  \n"CYAN"4"B_WHITE"::::"CYAN"444444"B_WHITE"::::" \
	CYAN"444    "YELLOW"22222"B_WHITE"::::::"YELLOW"22   \n"CYAN"4"B_WHITE \
	"::::::::::::::::"CYAN"4  "YELLOW"22"B_WHITE"::::::::"YELLOW"222     \n" \
	CYAN"4444444444"B_WHITE":::::"CYAN"444 "YELLOW"2"B_WHITE":::::"YELLOW \
	"22222        \n"CYAN"          4"B_WHITE"::::"CYAN"4  "YELLOW"2"B_WHITE \
	":::::"YELLOW"2             \n"CYAN"          4"B_WHITE"::::"CYAN"4  " \
	YELLOW"2"B_WHITE":::::"YELLOW"2             \n"CYAN"          4"B_WHITE \
	"::::"CYAN"4  "YELLOW"2"B_WHITE":::::"YELLOW"2       222222\n"CYAN \
	"        44"B_WHITE"::::::"CYAN"44"YELLOW"2"B_WHITE"::::::"YELLOW"2222222" \
	B_WHITE":::::"YELLOW"2\n"CYAN"        4"B_WHITE"::::::::"CYAN"4"YELLOW"2" \
	B_WHITE"::::::::::::::::::"YELLOW"2\n"CYAN"        4444444444" \
	YELLOW"22222222222222222222\n"RESET, mbox->executor.io.cmd_fd[CMD_OUT]);
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
}
