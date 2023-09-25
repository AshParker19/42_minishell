/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:25:35 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	Check if character is a white-space
 * 
 * @param 	c 
 * @return	int
 * 				1 = true
 * 				0 = false
 */
static int	ft_is_space(unsigned char c)
{
	if (c == ' ')
		return (1);
	else if (c == '\f')
		return (1);
	else if (c == '\n')
		return (1);
	else if (c == '\r')
		return (1);
	else if (c == '\t')
		return (1);
	else if (c == '\v')
		return (1);
	else
		return (0);
}

/**

 * @brief This function converts str into int removing ws in the front
 * 
 * @param str string to be converted 
 * @return int converted str
 */
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (ft_is_space(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	result = sign * result;
	return (result);
}
