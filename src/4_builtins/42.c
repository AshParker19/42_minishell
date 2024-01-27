/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:00:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/18 02:02:53 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   displays a pretty 42 logo to STDOUT (or its redirection)
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#42-builtin
 * 
 * @param   mbox        
 * @param   arg_node    
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
	YELLOW"22222222222222222222\n"RESET, mbox->exec.io.cmd_fd[CMD_OUT]);
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
}
