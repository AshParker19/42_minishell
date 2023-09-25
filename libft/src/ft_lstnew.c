/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:00:04 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	Allocates and returns a new node which will be initialized with
			the value of the parameter 'content'.
			The variable 'next' is initialized to NULL.
 * 
 * @param	content	The content to create the node with
 * @return	t_list* The new node
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list) * 1);
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
