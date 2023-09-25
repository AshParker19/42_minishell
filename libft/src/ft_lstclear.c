/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:11:23 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	I use this function as a function pointer parameter for ft_lstclear
 * 
 * @param	nothing will be the pointer to content of a linked list.
 */
void	null_ptr(void *nothing)
{
	(void)nothing;
}

/**
 * @brief	I use this function as a function pointer parameter for ft_lstclear
 * 			to free each nodes content
 * 
 * @param node	will be the pointer to content of a linked list.
 */
void	free_content(void *node)
{
	free(node);
}

/**
 * @brief	Deletes and frees the given node and every successor of that node,
 * 			using the function 'del' and 'ft_lstdelone'.
 * 			Finally, the pointer to the list is set to NULL.
 * 
 * @param lst	The address of a pointer to a node.
 * @param del	The address of a function used to delete the content of the node
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
	*lst = NULL;
}
