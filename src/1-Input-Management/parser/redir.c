/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:45 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/04 14:55:49 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *redir_case1(t_minibox *minibox);
static t_tree *redir_case2(t_minibox *minibox);

t_tree *redir_main(t_minibox *minibox)
{
    t_tree  *redir_node;
    t_token *backup;

    if (!minibox->tmp_token)
        return (NULL);
    backup = minibox->tmp_token;
    redir_node = redir_case1(minibox);
    if (redir_node)
        return (redir_node);
    minibox->tmp_token = backup;
    redir_node = redir_case2(minibox);
    if (redir_node)
        return (redir_node);
    return (NULL);
}

/* <redir in> */
static t_tree *redir_case1(t_minibox *minibox)
{
    t_tree  *redir_in_node;

    if (!minibox->tmp_token)
        return (NULL);
    if (minibox->tmp_token->type != RED_IN_TOKEN)
        return (NULL);
    if (!minibox->tmp_token->value)
        return (NULL);   
    redir_in_node = redir_in_main(minibox);
    return (redir_in_node);
}
/* <redir out> */
static t_tree *redir_case2(t_minibox *minibox)
{
    t_tree  *redir_out_node;

    if (!minibox->tmp_token)
        return (NULL);
    if (minibox->tmp_token->type != RED_OUT_TOKEN)
        return (NULL);
    if (!minibox->tmp_token->value)
        return (NULL);
    redir_out_node = redir_out_main(minibox);
    return (redir_out_node);   
}
