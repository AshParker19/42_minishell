/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr2str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:32:33 by astein            #+#    #+#             */
/*   Updated: 2023/12/04 23:38:26 by astein           ###   ########.fr       */
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
		if (!buf)
			return (NULL);
		buf[0] = c;
		return (buf);
	}
	else
	{
		buf = ft_calloc(2, sizeof(char));
		if (!buf)
			return (NULL);
		buf[0] = c;
		return (buf);
	}
}
