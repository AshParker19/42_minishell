/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:39:45 by astein            #+#    #+#             */
/*   Updated: 2023/10/17 15:15:37 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	free the pointer 'ptr'
 * 
 * @param	ptr pointer to be freed
 */
static void	free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

/**
 * @brief	frees each entry of the matrix/array and the pointer to the array
 * 			itself
 * 
 * @param	matrix	matrix/array to be freed
 */
static void	free_matrix(void **matrix)
{
	int	arr_i;

	arr_i = 0;
	if (matrix)
	{
		while (matrix[arr_i])
		{
			free(matrix[arr_i]);
			arr_i++;
		}
		free(matrix);	
	}	
}

/**
 * @brief	to simplify the freeing process this function can free
 * 				(symbol 'p')	pointers
 * 				(symbol 'm')	matrix (char**)
 * 				(symbol 'l')	linked lists of the struct type 't_list'
 * 
 * 			EXAMPLE:
 * 				char	*ptr;
 * 				char	**arr;
 * 				t_list	**lst;
 * 				free_whatever ("pal", ptr, arr, lst);
 * 
 * 			NOTE:	the content of nodes int the list are NOT freed!
 * 
 * @param	str		symols representing the argument types
 * @param	...		arguments to be freed
 * @return	void*	always 'NULL'
 */
void	*free_whatever(char *str, ...)
{
	va_list	args;

	va_start(args, str);
	while (*str)
	{
		if (*str == 'p')
			free_ptr(va_arg(args, void *));
		else if (*str == 'm')
			free_matrix(va_arg(args, void **));
		else if (*str == 'l')
			ft_lstclear(va_arg(args, t_list **), null_ptr);
		else if (*str == 'c')
			ft_lstclear(va_arg(args, t_list **), free_content);
		else
			ft_printf("bad param free_whatever: %c\n", str[0]);
		str++;
	}
	va_end(args);
	return (NULL);
}
