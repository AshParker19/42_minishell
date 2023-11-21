/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:43:17 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/21 18:59:42 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   this function frees and resets everthting thats needed to process
 *          one cycle
 * 
 *          NOTE:   only be called from 'main' before reading a new line
 * 
 * @param mbox 
 */
void    reset_cycle(t_mbox *mbox)
{
	free_cycle_v2 (mbox);
	mbox->executor.io.prev_pipe[P_LEFT] = -1;
	mbox->executor.io.prev_pipe[P_RIGHT] = -1;
	mbox->executor.pid_index = 0;
	update_signals(SIGNAL_MAIN);
	g_signal_status = 0;
	mbox->consecutive_lt = 0;
}

void	*create_syntax_err(t_mbox *mbox, t_token *err_token)
{
	if (mbox->error_status == ft_false)
	{
		mbox->error_status = ft_true;
		if(err_token && err_token->value)
			err_msg(mbox, 2, "nnnn", ERR_P, SE_UT, err_token->value, SQ);
		else
			err_msg(mbox, 2, "nn", ERR_P, SE_NL);
	}
	if (err_token)
		mbox->tmp_token = err_token->next;
	return(NULL);
}

static void    tmp_conclusion(t_mbox *mbox, char *err_msg, int exit_status)
{
	if (err_msg)
	{
		ft_putendl_fd(err_msg, STDERR_FILENO);    
		free (err_msg);
	}
	if (exit_status != NO_EXIT_STATUS)
		set_var_value_int(mbox, "?", exit_status);
}

/**
 * @brief   uses variadic variables to create a custom error message dynamically
 *          uses format string as an identifier if any of the accepted string
 *          should be allocated
 * 
 *err_msg("ccaca", "HI", "HI", ft_strup(), "HI", random_allocated_char)
 *                   n = no =  constant string   -> free needed
 *                   y = yes = allocated         -> need to be freed
 * 
 * @param   format 
 * @param   ... 
 */
void    err_msg(t_mbox *mbox, int exit_status, const char *format, ...)
{
	va_list	args;
	char    *err_msg;
	char    *str;

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
	tmp_conclusion(mbox, err_msg, exit_status);
}

/**
 * @brief 		NOTE:
 * 				This function can be uses similar like
 * 				dprintf(2, ...);
 * 
 * 				But it only will be printed if minishell is run with --info
 * 
 * @param mbox 
 * @param color 
 * @param format 
 * @param ... 
 */
void    put_info_msg(t_mbox *mbox, const char *format, ...) //this function wasnt freeing properly so I removed it for the time being
{
	va_list	args;
	char    *info_msg;
	char    *str;

	if (!mbox->print_info)
		return ;
	va_start(args, format);
	info_msg = ft_strdup(RED" >>>INFO MSG>>> \n"RESET);
	while (*format)
	{
		str = va_arg(args, char *);
		if (str)
		{
			info_msg = append_str(info_msg, str, ft_false);
			info_msg = append_str(info_msg, " ", ft_false);
			if (*format == 'y')
				free (str);
		}
		format++;
	}
	va_end(args);
	tmp_conclusion(mbox, info_msg, NO_EXIT_STATUS);	
}

