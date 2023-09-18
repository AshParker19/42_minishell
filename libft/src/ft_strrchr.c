/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:23:53 by astein            #+#    #+#             */
/*   Updated: 2023/08/07 16:11:14 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief	This function returns a pointer to the last occurrence of the
 * 			character 'c' in the string 's'.
 * 
 * @param	s 
 * @param	c 
 * @return	char* a pointer to the last occurrence of 'c' in 's'
 */
char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	ptr = &ptr[ft_strlen(s)];
	if ((unsigned char)c == '\0')
		return (ptr);
	ptr--;
	while (ptr >= (char *)s)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr--;
	}
	return (NULL);
}
