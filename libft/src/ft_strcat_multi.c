/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_multi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:32:33 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	see 'ft_strcat_multi()'
 * 
 * @param amount_of_strs	number of strings to concatenate
 * @param args				'va_list' holding the strings to concatenate
 * @param strs				[return]	resulting linked list with all strings
 * @param result			[return]	malloced space for the concatenation
 */
static void	malloc_result_str(int amount_of_strs, va_list args,
	t_list ***strs, char **result)
{
	size_t	len;
	int		i;
	char	*buffer;

	len = 0;
	i = -1;
	*strs = malloc(sizeof(t_list *));
	**strs = NULL;
	while (++i < amount_of_strs)
	{
		buffer = va_arg(args, char *);
		len += ft_strlen(buffer);
		ft_lstadd_back(*strs, ft_lstnew(buffer));
	}
	*result = ft_calloc(len + 1, sizeof(char));
}

/**
 * @brief	see 'ft_strcat_multi'
 * 
 * @param strs		linked list with all strings
 * @param result	[return]	all strings concatenated
 */
static void	fill_result_str(t_list **strs, char *result)
{
	size_t	len;
	char	*cur_ptr;
	t_list	*cur_node;

	cur_node = *strs;
	cur_ptr = result;
	while (cur_node)
	{
		len = ft_strlen(cur_node->content);
		ft_memcpy(cur_ptr, cur_node->content, len);
		cur_ptr += len;
		cur_node = cur_node->next;
	}
	free_whatever("lp", strs, strs);
	*cur_ptr = '\0';
}

/**
 * @brief	this function takes multiple string arguments (char*) and
 * 			concatenates them into 1 new malloced string. The number of string
 * 			must be defined in 'amount_of_strs'
 * 
 * 			to do so two functions are used:
 * 				'malloc_result_str'
 * 				'fill_result_str'
 *
 * 			'malloc_result_str'
 * 				- reads all args to calculate the total length of the new string
 * 				- stores all strings in a newly created linked list
 * 
 * 
 *			'fill_result_str' 
 * @param	amount_of_strs	number of strings to concatenate
 * @param	...				strings to concatenate
 * @return	char*			resulting string after concatenation
 */
char	*ft_strcat_multi(int amount_of_strs, ...)
{
	va_list	args;
	char	*result;
	t_list	**strs;

	strs = NULL;
	va_start(args, amount_of_strs);
	malloc_result_str(amount_of_strs, args, &strs, &result);
	va_end(args);
	fill_result_str(strs, result);
	return (result);
}
