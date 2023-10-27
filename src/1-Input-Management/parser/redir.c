/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:45 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/27 15:13:17 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *redir_case1(t_mbox *mbox);
static t_tree *redir_case2(t_mbox *mbox);

t_tree *redir_main(t_mbox *mbox)
{
    t_tree  *redir_node;
    t_token *backup;

    if (!mbox->tmp_token)
        return (NULL);
    backup = mbox->tmp_token;
    redir_node = redir_case1(mbox);
    if (redir_node)
        return (redir_node);
    mbox->tmp_token = backup;
    redir_node = redir_case2(mbox);
    if (redir_node)
        return (redir_node);
    return (NULL);
}

/* <redir in> */
static t_tree *redir_case1(t_mbox *mbox)
{
    t_tree  *redir_in_node;

    if (!mbox->tmp_token)
        return (NULL);
    if (mbox->tmp_token->type != RED_IN_TOKEN)
        return (NULL);
    if (!mbox->tmp_token->value)
        return (NULL);   
    redir_in_node = redir_in_main(mbox);
    return (redir_in_node);
}
/* <redir out> */
static t_tree *redir_case2(t_mbox *mbox)
{
    t_tree  *redir_out_node;

    if (!mbox->tmp_token)
        return (NULL);
    if (mbox->tmp_token->type != RED_OUT_TOKEN)
        return (NULL);
    if (!mbox->tmp_token->value)
        return (NULL);
    redir_out_node = redir_out_main(mbox);
    return (redir_out_node);   
}
