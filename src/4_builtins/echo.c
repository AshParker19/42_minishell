/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:13 by astein            #+#    #+#             */
/*   Updated: 2023/12/18 02:03:32 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   checks if the argument is a flag:
 * 			the only valid flag is '-n' that tells echo not to print a newline
 * 			the amount of '-n' flags is irrelevant	e.g. 'echo -n -n -n hello'
 * 			the amount of 'n' is irrelevant			e.g. 'echno -nn -nnn hello'
 * 
 * @param   arg         
 * @param   found_text  
 * @param   print_nl    
 * @return  t_bool      
 */
static t_bool	is_flag(char *arg, t_bool *found_text, t_bool *print_nl)
{
	int		i;
	t_bool	all_char_n;

	if (arg[0] != '-')
		*found_text = ft_true;
	else
	{
		i = 0;
		all_char_n = ft_false;
		while (arg[++i] != '\0')
		{
			if (arg[i] == 'n')
				all_char_n = ft_true;
			else
			{
				all_char_n = ft_false;
				break ;
			}
		}
		if (all_char_n)
			*print_nl = ft_false;
		else
			*found_text = ft_true;
	}
	return (!*found_text);
}

/**
 * @brief   The builtin echo command outputs the strings it is given as
 * 			arguments, seperated by one space each, to the standard output
 * 			(or its redirection).
 * 
 * 			FLAG:
 * 			if flag -n is not present (at least once) as FIRST ARG NODE:
 *              - adds a '\n'
 * 
 * 			NOTE:
 * 			'found_text' tells if an printable arg was found before then ignore
 * 			further flags and print all the args with spaces in between
 * 			(to deal with those cases)
 *	 			echo -n hello -n
 * 				echo -n -n hello
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#echo-builtin
 * 
 * @param   mbox        
 * @param   arg_node    
 */
void	builtin_echo(t_mbox *mbox, t_ast *arg_node)
{
	t_bool	print_nl;
	t_bool	found_text;	

	print_nl = ft_true;
	found_text = ft_false;
	while (arg_node)
	{
		if (found_text || !is_flag(arg_node->content, &found_text, &print_nl))
		{
			ft_putstr_fd(arg_node->content,
				mbox->exec.io.cmd_fd[CMD_OUT]);
			arg_node = arg_node->right;
			if (arg_node)
				ft_putchar_fd(' ', mbox->exec.io.cmd_fd[CMD_OUT]);
		}
		else
			arg_node = arg_node->right;
	}
	if (print_nl)
		ft_putchar_fd('\n', mbox->exec.io.cmd_fd[CMD_OUT]);
	set_var_value_int(mbox, "?", EXIT_SUCCESS);
}
