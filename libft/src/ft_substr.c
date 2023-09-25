/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:40:54 by astein            #+#    #+#             */
/*   Updated: 2023/05/21 01:49:50 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	Allocates and returns a substring from the string 's'.
			The substring begins at index 'start' and is of maximum size 'len'.
 * 
 * @param	s		The string from which to create the substring.
 * @param	start	The start index of the substring in the string 's'.	
 * @param	len		The maximum length of the substring.
 * @return	char*
 * 					The substring
 * 					NULL if the allocation fails
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	cpy_len;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (s_len <= start)
		cpy_len = 0;
	else if (s_len <= len)
		cpy_len = s_len - start;
	else
		cpy_len = len;
	sub = malloc(cpy_len + 1);
	if (!sub)
		return (NULL);
	if (s_len <= start)
		sub[0] = 0;
	else
		ft_strlcpy(sub, &s[start], cpy_len + 1);
	if (s_len > start && !sub)
		free(sub);
	return (sub);
}
