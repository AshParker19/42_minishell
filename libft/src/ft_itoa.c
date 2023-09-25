/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:25:14 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function counts the digits of 'c'.
 * 			If 'c' < 0 the result includes one digit for the negative sign "-"
 * 
 * @param	c 
 * @return	int 
 */
static int	count_digits(long c)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	if (c < 0)
	{
		c *= -1;
		i++;
	}
	while (c > 0)
	{
		c /= 10;
		i++;
	}
	return (i);
}

/**
 * @brief	Allocates and returns a string representing the integer n
 * 			received as an argument.
 * 
 * @param	n	the integer to convert
 * @return	char* 
 * 				The string representing the n.
				NULL if the allocation fails.
 */
char	*ft_itoa(int n)
{
	char	*result;
	long	lnbr;
	int		digits;

	lnbr = n;
	digits = count_digits(lnbr);
	result = ft_calloc(digits + 1, sizeof(char));
	if (!result)
		return (NULL);
	result[digits] = '\0';
	if (lnbr == 0)
		result[0] = '0';
	if (lnbr < 0)
	{
		result[0] = '-';
		lnbr *= -1;
	}
	result[digits] = '\0';
	while (lnbr > 0)
	{
		result[digits - 1] = lnbr % 10 + '0';
		lnbr /= 10;
		digits--;
	}
	return (result);
}
