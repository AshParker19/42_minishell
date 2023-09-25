/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:34:04 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function returns a pointer to a new string which is a duplicate
 * 			of the string 's'. Memory for the new string is obtained with malloc
 * 
 * @param	s 
 * @return	char*
 * 				returns a pointer to the duplicated string
 * 				NULL if the allocation fails
 */
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s) + 1;
	if (!s)
		return (NULL);
	dup = malloc(len);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len);
	return (dup);
}
