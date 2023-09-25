/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:19:24 by astein            #+#    #+#             */
/*   Updated: 2023/05/09 15:38:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_printf.h"

void	print_nbr(long nbr, int *len)
{
	if (nbr == -2147483648)
	{
		print_char('-', len);
		print_char('2', len);
		print_nbr(147483648, len);
	}
	else if (nbr < 0)
	{
		print_char('-', len);
		print_nbr(-nbr, len);
	}
	else if (nbr < 10)
		print_char(nbr + '0', len);
	else
	{
		print_nbr(nbr / 10, len);
		print_char((nbr % 10) + '0', len);
	}
}
