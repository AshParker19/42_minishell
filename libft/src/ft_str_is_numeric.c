/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:58:08 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/19 20:01:55 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/*
    Checks each char in a string
        true    = if all chars are numeric
        false   = otherwise
                = if str is NULL
*/
t_bool  ft_str_is_numeric(char *str)
{
    if (!str)
        return (ft_false);
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (ft_false);
        str++;
    }
    return (ft_true);
}

