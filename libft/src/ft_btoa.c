/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:39:45 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

/**
 * @brief	converts the boolean 'b' into a readable string defined by the
 * 			parameter 'flg'
 *
 * 			FLG:
 * 					0 = TRUE, FALSE
 * 					1 = ON, OFF
 * 
 * @param	b		boolean to be converted
 * @param	flg		parameter defining the resulting string
 * @return	char*	result of the conversion
 */
char	*ft_btoa(t_bool b, int flg)
{
	if (b)
	{
		if (flg == 0)
			return ("TRUE");
		else if (flg == 1)
			return ("ON");
	}
	else
	{
		if (flg == 0)
			return ("FALSE");
		else if (flg == 1)
			return ("OFF");
	}
	return (NULL);
}
