/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:09 by astein            #+#    #+#             */
/*   Updated: 2023/10/09 17:24:20 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_export(t_minibox *minibox, char *key_value_pair)
{
    char **values;

    values = ft_split(key_value_pair, '=');
    if (values[0])
        add_var(minibox, values[0], values[1]);
}
