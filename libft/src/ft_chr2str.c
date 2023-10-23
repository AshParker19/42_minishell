/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr2str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:32:33 by astein            #+#    #+#             */
/*   Updated: 2023/10/23 21:57:25 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	allocates memmory to create a null terminated string out of a char
 * 
 * @param	c		char to be converted 
 * @return 	char*	pointer to null terminated char string
 */
char	*ft_chr2str(char c)
{
	char	*buf;

	if (c == '\0')
	{
		buf = ft_calloc(1, sizeof(char));
		buf[0] = c;
		return (buf);
	}
	else
	{
		buf = ft_calloc(2, sizeof(char));
		buf[0] = c;
		return (buf);
	}
}
