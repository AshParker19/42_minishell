/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:57 by astein            #+#    #+#             */
/*   Updated: 2023/12/04 12:00:29 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_exit_exit(t_mbox *mbox, char *str)
{
	err_msg(mbox, 2, "nnnnn", ERR_P, "exit: ", str, CS, NAR);
	free_and_close_box_v2(mbox);
}

static t_bool	parse_str_to_long_long(char *str, long long *result)
{
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			if (*result > (LLONG_MAX - (*str - '0')) / 10)
				return (ft_false);
			*result = *result * 10 + (*str - '0');
		}
		else
			return (ft_false);
		str++;
	}
	return (ft_true);
}

/**
 * @brief	
 * 
 * 		FIXME: THIS COMMEND IS OLD! NEED TO UPDATE IT!!!
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
 *		exit 255
 * 		TODO: fix this funtion for big numbers
 * @param str 
 * @return int 
 */

/**
 * @brief		
 * 		FIXME: THIS COMMEND IS OLD! NEED TO UPDATE IT!!!
 * 				- Checks if the string is a valid long long
 * 				- If it is, it returns true and stores the result in nr
 * 				- If it isn't, it returns false and doesn't change nr
 * 
 * @param	str
 * @param	nr
 * @return	t_bool 
 */
static t_bool	is_long_long(char *str_nr, int *nr)
{
	int			sign;
	long long	result;
	char		*str;

	str = str_nr;
	if (*str == '\0')
		return (ft_false);
	if (str_cmp_strct(str, "-9223372036854775808"))
	{
		*nr = 0;
		return (ft_true);
	}
	sign = 1;
	result = 0;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!parse_str_to_long_long(str, &result))
		return (ft_false);
	if (result > 0 && sign == -1)
		result *= -1;
	*nr = (int)(result % 256);
	return (ft_true);
}

/**
 * @brief 
 *	 		FIXME: THIS COMMEND IS OLD! NEED TO UPDATE IT!!!
 * 			- Always prints exit to STDERR_FILENO
 * 			- exits the current process via 'free_and_close_box'
 * 			- or prints a err message
 * 			- (or both) :D
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
void	builtin_exit(t_mbox *mbox, t_ast *arg_node)
{
	int	exit_status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!arg_node)
		free_and_close_box_v2(mbox);
	else
	{
		if (is_long_long(arg_node->content, &exit_status))
		{
			if (arg_node->right)
			{
				if (get_var_value(mbox, "?")[0] == '0')
					set_var_value_int(mbox, "?", 1);
				err_msg(mbox, NO_EXIT_STATUS, "nnnn", ERR_P, "exit", CS, TMA);
			}
			else
			{
				set_var_value_int(mbox, "?", exit_status);
				free_and_close_box_v2(mbox);
			}
		}
		else
			err_exit_exit(mbox, arg_node->content);
	}
}
