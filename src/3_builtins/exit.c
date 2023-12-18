/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:57 by astein            #+#    #+#             */
/*   Updated: 2023/12/18 02:03:51 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

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
 * @brief   Checks if the string is a valid long long
 * 				- If it is, it returns ft_true and stores it (mod 256) in `nr`
 * 				- If it isn't, it returns false and doesn't change nr
 * 
 * @param   str_nr      
 * @param   nr          
 * @return  t_bool      
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
 * @brief   The builtin `exit` terminates the current process, outputs `exit` to
 * 			`STDERR` and if provided with a numeric argument, it sets the exit
 * 			status to that argument's value.
 * 
 * CASE:		EXAMPLES:	 EXITCODE:			PRINT:			EXITS:
 *	no arg 		'exit'		 last exit status	exit			yes
 *	not num		`exit a`	 2					exit & error	yes
 *	num	1 arg	'exit 42'	 42					exit			yes
 *	num	2+ args	'exit 42 42' if last != 0		exit			no
 *							 	previous exit status
 * 							 else
 * 								1
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#exit-builtin
 * 
 * @param   mbox        
 * @param   arg_node    
 */
void	builtin_exit(t_mbox *mbox, t_ast *arg_node)
{
	int	exit_status;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!arg_node)
		destroy_mbox(mbox);
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
				destroy_mbox(mbox);
			}
		}
		else
		{
			err_msg(mbox, 2, "nnnnn", ERR_P, "exit: ", arg_node->content, CS, NAR);
			destroy_mbox(mbox);
		}
	}
}
