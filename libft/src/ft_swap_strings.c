/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:14:57 by astein            #+#    #+#             */
/*   Updated: 2023/12/05 00:58:14 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief   swaps to char pointers
 *          so if           a=foo and b=bar
 *          it changes to   a=bar and b=foo
 * 
 * @param   a   char to swap
 * @param   b   char to swap
 */
void	ft_swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
