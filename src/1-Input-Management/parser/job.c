/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:49:29 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/04 13:26:27 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *job_case1(t_minibox *minibox);
static t_tree *job_case2(t_minibox *minibox);

t_tree *job_main(t_minibox *minibox)
{
    t_tree  *job_node;
    t_token *backup;

    backup = minibox->tmp_token;
     if (!minibox->tmp_token)
        return (NULL);
    job_node = job_case1(minibox);
    if (job_node)
        return (job_node);
    minibox->tmp_token = backup;
    job_node = job_case2(minibox);
    if (job_node)
        return (job_node);
    minibox->tmp_token = backup;
    return (NULL);      
}

static t_tree *job_case1(t_minibox *minibox)
{
    (void)minibox;
    return (NULL);
}

static t_tree *job_case2(t_minibox *minibox)
{
    (void)minibox;
    return (NULL);
}
