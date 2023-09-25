/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:58:03 by astein            #+#    #+#             */
/*   Updated: 2023/05/26 21:07:08 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	Allocates and returns a copy of 's1' with the characters specified 
 * 			in 'set' removed from the beginning and the end of the string
 * 
 * @param	s1	The string to be trimmed
 * @param	set The reference set of characters to trim
 * @return	char*
 * 				The trimmed string
 * 				NULL if the allocation fails
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i > 0 && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
