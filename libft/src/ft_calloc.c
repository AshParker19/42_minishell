/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:17:50 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	This function  allocates  memory  for  an  array of 'nmemb' elements
 * 			of 'size' bytes each and returns a pointer to the allocated memory.
 * 			The memory is set to zero.
 * 
 * @param 	nmemb 
 * @param 	size 
 * @return 	void* 
 * 				a pointer to the allocated memory
 *				NULL if the allocation fails
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	bytes;

	bytes = nmemb * size;
	ptr = malloc(bytes);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, bytes);
	return (ptr);
}
