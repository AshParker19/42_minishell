/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:25:23 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function locates the first occurrence of the null-terminated
 * 			string 'little' in the string 'big', where not more than 'len'
 * 			characters are searched.
 * 			Characters that appear after a '\0' character are not searched.
 * 
 * @param	big 
 * @param	little 
 * @param 	len 
 * @return	char*
 * 				If 'little' is an empty string, 'big' is returned
 * 				if 'little' occurs nowhere in 'big', NULL is returned
 * 				otherwise a pointer to the first character of the first
 * 				occurrence of 'little' is returned. 
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	result = (char *)big;
	if (!little[0])
		return (result);
	while (result[i] && i < len)
	{
		j = 0;
		while (result[i + j] == little[j] && i + j < len)
		{
			j++;
			if (little[j] == '\0')
				return (&result[i]);
		}
		i++;
	}
	return (NULL);
}
