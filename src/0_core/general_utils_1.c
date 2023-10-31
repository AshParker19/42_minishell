/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:43:17 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/31 17:59:06 by astein           ###   ########.fr       */
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

/*
    create_error_msg("ccaca", "HI", "HI", ft_strup(), "HI", random_allocated_char)
                    n = no =  constant string   -> free needed
                    y = yes = allocated         -> need to be freed
*/

/**
 * @brief   uses variadic variables to create a custom error message dynamically
 *          uses format string as an identifier if any of the accepted string
 *          should be allocated
 * 
 * @param   format 
 * @param   ... 
 */
void    create_error_msg(const char *format, ...)
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

