/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:32:33 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function appends the NULL-terminated string 'src' to the end of
 * 			'dst'. It will append at most size - strlen(dst) - 1 bytes
 * 			'dst' will be NULL terminated.
 * 
 * @param	dst 
 * @param	src 
 * @param	size 
 * @return	size_t	the initial length of 'dst' plus the length of 'src'
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len;

	len = ft_strlen(dst);
	i = 0;
	if (!size || size <= len)
		return (ft_strlen(src) + size);
	while (i < (size - len - 1) && src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (len + ft_strlen(src));
}
