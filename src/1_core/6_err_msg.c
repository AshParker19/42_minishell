/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_err_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 01:15:04 by astein            #+#    #+#             */
/*   Updated: 2023/12/19 02:08:50 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "frankenshell.h"

/**
 * @brief   Uses ellipsis (...) to create a custom error message dynamically.
 *          uses format string as an identifier if any of the accepted string
 *          is allocated and therefore needs to be freed.
 * 
 * err_msg("nyny", "HI", ft_strup(), "HI", random_allocated_char)
 *		n = no =  constant string   -> free needed
 * 		y = yes = allocated         -> need to be freed
 * 
 * @param   mbox        
 * @param   exit_status Additionaly sets the exit status if != NO_EXIT_STATUS
 * @param   format      
 * @param   ...         
 */
void	err_msg(t_mbox *mbox, int exit_status, const char *format, ...)
{
	va_list	args;
	char	*err_msg;
	char	*str;

	va_start(args, format);
	err_msg = NULL;
	while (*format)
	{
		str = va_arg(args, char *);
		if (str)
		{
			if (!err_msg)
				err_msg = ft_strdup(str);
			else
			{
				err_msg = append_str(err_msg, str, ft_false);
				if (*format == 'y')
					free (str);
			}
		}
		format++;
	}
	va_end(args);
	if (err_msg)
	{
		ft_putendl_fd(err_msg, STDERR_FILENO);
		free (err_msg);
	}
	if (exit_status != NO_EXIT_STATUS)
		set_var_value_int(mbox, "?", exit_status);
}

/**
 * @brief   Special error message for syntax errors created via `err_msg`
 * 			Only the first syntax error per cycle will be printed thanks to the
 * 			`syntax_err_encountered` flag
 * 
 * 			Syntax errors result in updating the exit status to 2
 * 
 * @param   mbox        
 * @param   err_token   
 * @return  void*       
 */
void	*syntax_err_msg(t_mbox *mbox, t_token *err_token)
{
	if (mbox->syntax_err_encountered == ft_false)
	{
		mbox->syntax_err_encountered = ft_true;
		if (err_token && err_token->value)
			err_msg(mbox, 2, "nnnn", ERR_P, SE_UT, err_token->value, SQ);
		else
			err_msg(mbox, 2, "nn", ERR_P, SE_NL);
	}
	if (err_token)
		mbox->tmp_token = err_token->next;
	return (NULL);
}