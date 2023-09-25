/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:39:45 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	converts a double into a string with 'digits' decimal places
 * 
 * 			WARNING:	the function is NOT rounding the double properly!
 * 
 * @param d			double to be converted
 * @param digits	amount of decimal places
 * @return char*	result of doulbe to string convertion
 */
char	*ft_dtoa(double d, unsigned int digits)
{
	long	part_int;
	double	part_dec;
	char	*result;
	char	*buffer[2];

	part_int = (int)d;
	part_dec = fabs(d - part_int);
	part_dec *= pow(10, digits);
	part_dec = (int)(part_dec);
	buffer[0] = ft_itoa(part_int);
	buffer[1] = ft_itoa((int)part_dec);
	if (digits > 0)
		result = ft_strcat_multi(3, buffer[0], ".", buffer[1]);
	else
		result = ft_strcat_multi(1, buffer[0]);
	free_whatever ("pp", buffer[0], buffer[1]);
	return (result);
}
