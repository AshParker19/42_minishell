/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:24:22 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function compares the first (at most) 'n' bytes of the two
 * 			strings 's1' and 's2'.
 *
 * @param	s1
 * @param	s2 
 * @param	n	number of bytes which should be compared
 * @return	int	value less than, equal to, or greater than zero if 's1' is 
 * 				found, respectively, to be less than, to match,
 * 				or be greater than 's2'.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len1;
	size_t	len2;
	size_t	len;

	len1 = ft_strlen(s1) + 1;
	len2 = ft_strlen(s2) + 1;
	len = n;
	if (len > len1 || len > len2)
	{
		if (len1 > len2)
			len = len2;
		else
			len = len1;
	}
	return (ft_memcmp(s1, s2, len));
}
