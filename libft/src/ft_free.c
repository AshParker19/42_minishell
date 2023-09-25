/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:39:45 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
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
 * @brief	frees each entry of the array and the pointer to the array itself
 * 
 * @param	arr	array to be freed
 */
static void	free_arr(void **arr)
{
	int	arr_i;

	arr_i = 0;
	while (arr[arr_i])
	{
		free(arr[arr_i]);
		arr_i++;
	}
	free(arr);
}

/**
 * @brief	to simplify the freeing process this function can free
 * 				(symbol 'p')	pointers
 * 				(symbol 'a')	arrays
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
		else if (*str == 'a')
			free_arr(va_arg(args, void **));
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
