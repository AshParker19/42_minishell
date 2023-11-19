/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_chr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:08:38 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/19 23:31:33 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

void	ft_lstiter_chr(t_list *lst, void (*f)(void *, char *, char *), char *str, char *value)
{
	while (lst)
	{
		f(lst->content, str, value);
		lst = lst->next;
	}
}