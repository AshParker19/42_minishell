/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:57 by astein            #+#    #+#             */
/*   Updated: 2023/11/11 15:02:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief	checks if the argument is numeric:
 * 
 *		YES:						|	NO:
 *		(exit code % 128)			|	err_msg (exits code 2)
 *		--------------------------------------------------------
 *		EXAMPLES:		RETURN:		|	EXAMPLES:
 *		exit 42			42			|	exit a
 *		exit -42		214			|	exit a a
 *		exit 424242		50			|	exit a 1
 *		exit 0 a		0			|
 *		exit 1 1		1			|
 * 
 * @param str 
 * @return int 
 */
static int is_exit_code_num(t_mbox *mbox, char *str)
{
	int exit_code;

	exit_code = ft_atoi(str);
	if(exit_code == 0 && str[0] != '0')
	{
		put_err_msg(mbox, 2,"nnnn", ERR_PROMT, "exit: ", str,
			": numeric argument required");
		free_and_close_box_v2(mbox);	
	}
	return (exit_code % 128);
}

// TODO: check signal 

/**
 * @brief   exits the current process via 'free_and_close_box' or prints a err
 * 			message or both :D
 * 			or prints exit but doesnt exit just like the official bash :D
 * 
 *	CASE:		EXAMPLES:					EXITCODE:			PRINT:	EXITS:
 *	no arg 		'exit'						last exit status	exit	yes
 *	not num		see: 'is_exit_code_num'		2					exit	yes
 *	num	1 arg	'exit 42'					42					exit	yes
 *	num	2+ args	'exit 42 42','exit 42 a'	if last != 0		exit	no
 * 												old one
 * 											else
 * 												1
 * @param   mbox 		
 * @param   arg_node 
 */
void    builtin_exit(t_mbox *mbox, t_ast *arg_node)
{
	int exit_status;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if(!arg_node)
        free_and_close_box_v2(mbox);
	else
	{
		exit_status = is_exit_code_num(mbox, arg_node->content);	
		if (arg_node->right)
		{
			if (get_var_value(mbox, "?")[0] == '0')
				set_var_value_int(mbox, "?", 1);	
			put_err_msg(mbox, NO_EXIT_STATUS,"nn", ERR_PROMT, "exit: too many arguments");
			free_cycle_v2(mbox);
		}
		else
		{
			set_var_value_int(mbox, "?", exit_status);
			free_and_close_box_v2(mbox);	
		}
	}
}
