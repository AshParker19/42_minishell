/* ************************************************************************** */
/*                                                              */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:04:49 by astein            #+#    #+#             */
/*   Updated: 2023/04/21 10:58:43 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	Takes next arg from 'args' and a type identifier 'str' to call the
 * 			matching print_function of numbers with decimal digits
 * 
 * 			EXAMPLE:	ft_printf("here a double %d3\n", 12.3456); -> 12.345
 * 			WARNING:	'ft_dtoa' is NOT rounding the double properly!
 * 
 * @param	args	va_list with all the arguments
 * @param	str		type identifier (d<NUM>)	with 0 <= NUM <= 9
 * @return	int		length of printed string
 */
int	print_whatever_digits(va_list args, char *str)
{
	int		len;
	char	*digits;
	char	*str_nbr;

	len = 0;
	if (*str == 'd')
	{
		if (*str == 'd')
		{
			str++;
			digits = malloc(sizeof(char) * 2);
			ft_strlcpy(digits, str, 2 * sizeof(char));
			str_nbr = ft_dtoa(va_arg(args, double), ft_atoi(digits));
			print_str(str_nbr, &len);
			free_whatever("pp", digits, str_nbr);
		}
	}
	return (len);
}

/**
 * @brief	Takes next arg from 'args' and a type identifier 'str' to call the
 * 			matching print_function.
 * 
 * @param	args	va_list with all the arguments
 * @param	str		type identifier (%cspdiuxX)	
 * @return	int		length of printed string
 */
int	print_whatever(va_list args, char *str)
{
	int	len;

	len = 0;
	if (*str == '%')
		print_char('%', &len);
	else if (*str == 'c')
		print_char(va_arg(args, int), &len);
	else if (*str == 's')
		print_str(va_arg(args, char *), &len);
	else if (*str == 'p')
		print_ptr(va_arg(args, unsigned long), &len);
	else if (*str == 'i')
		print_nbr(va_arg(args, int), &len);
	else if (*str == 'u')
		print_nbr(va_arg(args, unsigned int), &len);
	else if (*str == 'x')
		print_dez_to_hexa(va_arg(args, unsigned int), &len, ft_false);
	else if (*str == 'X')
		print_dez_to_hexa(va_arg(args, unsigned int), &len, ft_true);
	return (len);
}

/**
 * @brief	This function prints the string 'str' while replacing the 
 * 			identifiers (%cspdiuxXd) with values from va_list
 * 
 * @param 	str	string to be printed
 * @param 	... values to be printed
 * @return	int	length of printed string
 */
int	ft_printf(const char *str, ...)
{
	int		len;
	int		len_add;
	va_list	args;

	len = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			len_add = 0;
			len_add = print_whatever(args, (char *)str);
			if (len_add == 0)
				len_add = print_whatever_digits(args, (char *)(str++));
			len += len_add;
		}
		else
			print_char(*str, &len);
		str++;
	}
	va_end(args);
	return (len);
}
