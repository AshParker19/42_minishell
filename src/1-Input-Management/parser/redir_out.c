/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:24:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/03 20:46:37 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *redir_out_case1(t_minibox *minibox);
static t_tree *redir_out_case2(t_minibox *minibox);

t_tree *redir_out_main(t_minibox *minibox)
{
    t_tree  *red_out_node;
    t_token *backup;

    backup = minibox->tmp_token;
    if (!minibox->tmp_token)
        return (NULL);
    red_out_node = redir_out_case1(minibox);
    if (red_out_node)
        return (red_out_node);
    minibox->tmp_token = backup;
    red_out_node = redir_out_case2(minibox);
    if (red_out_node)
        return (red_out_node);
    return (NULL);
}

static t_tree *redir_out_case1(t_minibox *minibox)
{
    t_tree  *red_out_ap_node;

    if (!minibox->tmp_token)
        return (NULL);
    if (minibox->tmp_token->type != RED_OUT_TOKEN)
        return (NULL);
    if (!minibox->tmp_token->value)
        return (NULL);
    
    if (!minibox->tmp_token->next)
        return (NULL);
    if (minibox->tmp_token->next->type != RED_OUT_TOKEN)
        return (NULL);
    if (!minibox->tmp_token->next->value)
        return (NULL);
    
    red_out_ap_node = ast_create_node(RED_OUT_AP);
    red_out_ap_node->content = ft_strdup(">>");
    minibox->tmp_token = minibox->tmp_token->next->next;
    return (red_out_ap_node);
}
static t_tree *redir_out_case2(t_minibox *minibox)
{
    t_tree  *red_out_tr_node;
    
    if (!minibox->tmp_token)
        return (NULL);
    if (minibox->tmp_token->type != RED_OUT_TOKEN)
        return (NULL);
    if (!minibox->tmp_token->value)
        return (NULL);

    red_out_tr_node = ast_create_node(RED_OUT_TR);
    red_out_tr_node->content = ft_strdup(">");
    minibox->tmp_token = minibox->tmp_token->next;
    return (red_out_tr_node);
}