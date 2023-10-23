/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:14:28 by astein            #+#    #+#             */
/*   Updated: 2023/10/23 18:32:31 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft_printf.h"

/**
 * @brief   Checks each char in a string if is nummeric
 * 
 * @param   str string to check
 * @return  t_bool 
 *              ft_true    = if all chars are numeric
 *              ft_false   = otherwise or if str is NULL
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

