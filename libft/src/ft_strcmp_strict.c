/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_strict.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 00:57:29 by astein            #+#    #+#             */
/*   Updated: 2023/12/05 01:00:34 by astein           ###   ########.fr       */
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
t_bool	str_cmp_strct(const char *str_a, const char *str_b)
{
	if (!str_a || !str_b)
		return (ft_false);
	if (ft_strlen(str_a) == ft_strlen(str_b))
		if (!ft_strncmp(str_a, str_b, ft_strlen(str_a)))
			return (ft_true);
	return (ft_false);
}
