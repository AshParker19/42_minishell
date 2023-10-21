/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:14:28 by astein            #+#    #+#             */
/*   Updated: 2023/10/20 20:14:29 by astein           ###   ########.fr       */
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

