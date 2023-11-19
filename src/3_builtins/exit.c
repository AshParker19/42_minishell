/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:57 by astein            #+#    #+#             */
/*   Updated: 2023/11/19 18:01:08 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void err_exit_exit(t_mbox *mbox, char *str)
{
	err_msg(mbox, 2,"nnnnn", ERR_P, "exit: ", str, CS, NAR);
	free_and_close_box_v2(mbox);
}

static int isMultiplySafe(long long a) {
    return (a <= LLONG_MAX / 10);
}

// Function to check for potential overflow before addition
static int isAdditionSafe(long long a, long long b) {
    return (a <= LLONG_MAX - b);
}

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
 * 		TODO: fix this funtion for big numbers
 * @param str 
 * @return int 
 */
static int is_exit_code_num(t_mbox *mbox, char *s)
{
	long long exit_code;
	int		  sign;
	char *str;
	
	str = s;
	// dprintf(2, "%l" , LLONG_MAX);
	exit_code = 0;
	sign = 1;
	str = ft_strtrim(str, "+");
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			break ;
		 if (!isMultiplySafe(exit_code))
			err_exit_exit(mbox, str);	
		if (!isAdditionSafe(exit_code * 10, (*str - '0')))
			err_exit_exit(mbox, str);
		exit_code = exit_code * 10 + (*str - '0');
		str++;
	}
	exit_code *= sign;
	// 	err_exit_exit(mbox, str);
	// dprintf(2, "exit_code: %lld\n", exit_code);
	// exit_code = ft_atoi(str);
	if(*str || (exit_code == 0 && s[0] != '0'))
	{
		err_msg(mbox, 2,"nnnnn", ERR_P, "exit: ", str, CS, NAR);
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
			err_msg(mbox, NO_EXIT_STATUS,"nnnn", ERR_P, "exit", CS, TMA);
			free_cycle_v2(mbox);
		}
		else
		{
			set_var_value_int(mbox, "?", exit_status);
			free_and_close_box_v2(mbox);	
		}
	}
}
