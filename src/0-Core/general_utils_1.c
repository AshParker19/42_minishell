/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:43:17 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/14 18:05:48 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*
//     create_error_msg("ccaca", "HI", "HI", ft_strup(), "HI", random_allocated_char)
//                     c = constant -> no free needed
//                     a = allocated -> need to be freed
// */
// void    create_error_msg(const char *str, ...)
// {
// 	va_list	args;
//     int     count_of_parts;
//     char    *msg;

// 	va_start(args, str);
//     count_of_parts = ft_strlen(str);
    
//     msg = ft_strcat_multi(count_of_parts, va_arg(args, int));
    
// 	va_end(args);
// }