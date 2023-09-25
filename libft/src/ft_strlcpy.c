/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:21:56 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function copies up to size - 1 characters from the 
 * 			NULL-terminated string 'src' to 'dst'.
 * 			'dest' will be NULL terminated.
 * 
 * @param	dst 
 * @param	src 
 * @param	size 
 * @return	size_t	the length of 'src'
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size)
	{
		i = 0;
		while (src[i] && (i < (size - 1)))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}
