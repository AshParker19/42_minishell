/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace_chr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:32:33 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	replaces all char 'old' in string 'str' with char 'new'
 * 
 * @param str	string to replaces chars in
 * @param old	char to be replaced
 * @param new	char to be replaced with
 */
void	ft_str_replace_chr(char *str, char old, char new)
{
	while (*str != '\0')
	{
		if (str[0] == old)
			*str = new;
		str++;
	}
}
