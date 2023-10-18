/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:43:17 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/18 14:02:12 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    create_error_msg("ccaca", "HI", "HI", ft_strup(), "HI", random_allocated_char)
                    c = constant -> no free needed
                    a = allocated -> need to be freed
*/
void    create_error_msg(const char *format, ...)
{
	va_list	args;
    char    *erorr_msg;
    const char    *copy;
    char    *str;
    int     count;

    count = 0;
	va_start(args, format);
    // count_of_parts = ft_strlen(format);
    copy = format;
    while (*copy)
    {
        str = va_arg(args, char *);
        while (*str)
        {
            count++;
            str++;
        }
        copy++;
    }
    printf ("COUNT %d\n", count);
    // msg = ft_strcat_multi(count_of_parts, va_arg(args, int));
    
	va_end(args);
}