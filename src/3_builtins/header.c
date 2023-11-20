/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:00:32 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/20 23:35:05 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

# define B_WHITE "\x1b[97m"

void	builtin_header(t_mbox *mbox, t_ast *arg_node)
{
	(void)arg_node;
	ft_putstr_fd(CYAN"       444444444   "YELLOW"222222222222222    \n"\
	CYAN"      4"B_WHITE"::::::::"CYAN"4  "YELLOW"2"B_WHITE":::::::::::::::"\
	YELLOW"22  \n"CYAN"     4"B_WHITE":::::::::"CYAN"4  "YELLOW"2"B_WHITE\
	"::::::"YELLOW"222222"B_WHITE":::::"YELLOW"2 \n"CYAN"    4"B_WHITE"::::"\
	CYAN"44"B_WHITE"::::"CYAN"4  "YELLOW"2222222     2"B_WHITE":::::"YELLOW"2 \n"
	CYAN"   4"B_WHITE"::::"CYAN"4 4"B_WHITE"::::"CYAN"4              "YELLOW"2"\
	B_WHITE":::::"YELLOW"2 \n"CYAN"  4"B_WHITE"::::"CYAN"4  4"B_WHITE"::::"\
	CYAN"4              "YELLOW"2"B_WHITE":::::"YELLOW"2 \n"CYAN" 4"B_WHITE\
	"::::"CYAN"4   4"B_WHITE"::::"CYAN"4           "YELLOW"2222"B_WHITE"::::"\
	YELLOW"2  \n"CYAN"4"B_WHITE"::::"CYAN"444444"B_WHITE"::::"CYAN"444    "\
	YELLOW"22222"B_WHITE"::::::"YELLOW"22   \n"CYAN"4"B_WHITE"::::::::::::::::"\
	CYAN"4  "YELLOW"22"B_WHITE"::::::::"YELLOW"222     \n"CYAN"4444444444"\
	B_WHITE":::::"CYAN"444 "YELLOW"2"B_WHITE":::::"YELLOW"22222        \n"
	CYAN"          4"B_WHITE"::::"CYAN"4  "YELLOW"2"B_WHITE":::::"YELLOW\
	"2             \n"CYAN"          4"B_WHITE"::::"CYAN"4  "YELLOW"2"\
	B_WHITE":::::"YELLOW"2             \n"CYAN"          4"B_WHITE"::::"\
	CYAN"4  "YELLOW"2"B_WHITE":::::"YELLOW"2       222222\n"CYAN"        44"\
	B_WHITE"::::::"CYAN"44"YELLOW"2"B_WHITE"::::::"YELLOW"2222222"B_WHITE":::::"\
	YELLOW"2\n"CYAN"        4"B_WHITE"::::::::"CYAN"4"YELLOW"2"\
	B_WHITE"::::::::::::::::::"YELLOW"2\n"CYAN"        4444444444"\
	YELLOW"22222222222222222222\n", mbox->executor.io.cmd_fd[CMD_OUT]);
	set_var_value(mbox, "?", EXIT_SUCCESS_STR);
}

