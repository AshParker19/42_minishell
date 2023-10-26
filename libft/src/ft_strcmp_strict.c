/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_strict.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:14:43 by astein            #+#    #+#             */
/*   Updated: 2023/10/23 18:34:05 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief   This function takes two strings and compares:
 *              - they need to have the same length
 *              - and all characters have to match
 * 
 * @param   str_a   string to compare
 * @param   str_b   string to compare
 * @return  t_bool
 *              ft_true    if they match (all chars and length)
 *              ft_false   if they don't and if any doesnt exist
 */
t_bool  ft_strcmp_strict(const char *str_a, const char *str_b)
{
    if(!str_a || !str_b)
        return (ft_false);
    if (ft_strlen(str_a) == ft_strlen(str_b))
        if (!ft_strncmp(str_a, str_b, ft_strlen(str_a)))
            return (ft_true);
    return (ft_false);
}
