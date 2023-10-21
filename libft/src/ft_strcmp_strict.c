/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_strict.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:14:43 by astein            #+#    #+#             */
/*   Updated: 2023/10/20 20:14:45 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/* This function takes two strings and compares:
    - they need to have the same length
    - and all characters have to match

    return bool
        true    if they match
        false   if they don't
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
