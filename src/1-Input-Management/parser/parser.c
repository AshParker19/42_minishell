/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/10/28 18:02:32 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	parse(t_mbox *mbox)
{
    mbox->tmp_token = mbox->tokens;
    mbox->root = job_main(mbox);
    
    if (mbox->tmp_token)
    {
        put_syntax_error(mbox, mbox->tmp_token);
        return (ft_false);
    }
    return (ft_true);
}
