/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:11:48 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	Iterates the list 'lst' and applies the function 'f' on the content
 * 			of each node. Creates a new list resulting of the successive
 * 			applications of the function 'f'. The 'del' function is used to
 * 			delete the content of a node if needed.
 * 
 * @param	lst		The address of a pointer to a node.
 * @param	f		The address of the function used to iterate on the list.
 * @param 	del		The address of the function used to delete the content of
 * 					a node if needed.
 * @return	t_list*	The new list.
					NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	void	*new_content;

	new_lst = NULL;
	while (lst)
	{
		new_content = (f(lst->content));
		if (new_content)
			ft_lstadd_back(&new_lst, ft_lstnew(new_content));
		else
			del(lst->content);
		lst = lst->next;
	}
	return (new_lst);
}
