/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:25:08 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function compares the first 'n' bytes of 's1' and 's2'
 * 			(each interpreted as unsigned char) 
 * 
 * @param	s1 
 * @param	s2 
 * @param	n	number of bytes which should be compared
 * @return	int
 * 				value less than, equal to, or greater than zero if the first 'n'
 * 				bytes of 's1' is found, respectively, to be less than, to match,
 * 				or be greater than the first 'n' bytes of 's2';
 * 				If 'n' is zero, the return (value is 0);
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && c1[i] == c2[i])
		i++;
	return ((int)c1[i] - (int)c2[i]);
}
