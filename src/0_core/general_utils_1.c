/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:43:17 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/07 21:01:10 by anshovah         ###   ########.fr       */
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
}

void    err_free_and_close_box(t_mbox *mbox, int exit_status)
{
    set_var_value(mbox, "?", ft_itoa(exit_status));
    free_and_close_box_v2(mbox);
}

void	*create_syntax_err(t_mbox *mbox, t_token *err_token)
{
	if (mbox->error_status == ft_false)
	{
		mbox->error_status = ft_true;
		if(err_token && err_token->value)
			put_err_msg("nnnn", ERR_PROMT,
				"syntax error near unexpected token `", err_token->value,"'" );
		else
			put_err_msg("nn", ERR_PROMT,
				"syntax error near unexpected token `newline'");
	}
	if (err_token)
		mbox->tmp_token = err_token->next;
	return(NULL);
}

/**
 * @brief   uses variadic variables to create a custom error message dynamically
 *          uses format string as an identifier if any of the accepted string
 *          should be allocated
 * 
 *put_err_msg("ccaca", "HI", "HI", ft_strup(), "HI", random_allocated_char)
 *                   n = no =  constant string   -> free needed
 *                   y = yes = allocated         -> need to be freed
 * 
 * @param   format 
 * @param   ... 
 */
void    put_err_msg(const char *format, ...)
{
	va_list	args;
    char    *error_msg;
    char    *temp;
    char    *str;

	va_start(args, format);
    error_msg = NULL;
    while (*format)
    {
        str = va_arg(args, char *);
        if (str)
        {
            if (!error_msg)
                error_msg = ft_strdup(str);
            else
            {
                temp = ft_strjoin(error_msg, str);
                free (error_msg);
                error_msg = temp;
                if (*format == 'y')
                    free (str);
            }
        }
        format++;
    }
	va_end(args);
    if (error_msg)
    {
        ft_putendl_fd(error_msg, STDERR_FILENO);    
        free (error_msg);
    }
}

