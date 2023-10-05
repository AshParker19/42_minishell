/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/10/05 17:06:40 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_minibox *minibox)
{
    minibox->tmp_token = minibox->tokens;
    minibox->root = job_main(minibox);
    if(minibox->root)
        printf("ROOT: %s\n",minibox->root->content);
    else
        printf("ROOT IS NULL\n");
    //TODO:
}
