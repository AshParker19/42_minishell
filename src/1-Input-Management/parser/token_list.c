/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:29 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/06 10:58:24 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *token_list_case1(t_minibox *minibox);
static t_tree *token_list_case2(t_minibox *minibox);
static t_tree *token_list_case3(t_minibox *minibox);

void token_list_main(t_minibox *minibox)
{
    t_tree  *tl_node;
    t_token *backup;

    backup = minibox->tmp_token;
    if (!minibox->tmp_token)
        return ;
    tl_node = token_list_case1(minibox);
    if (tl_node)
        return ;
    minibox->tmp_token = backup;
    tl_node = token_list_case2(minibox);
    if (tl_node)
        return ;
    minibox->tmp_token = backup;
    tl_node = token_list_case3(minibox);
}
/* [name]  <token list> */
static t_tree *token_list_case1(t_minibox *minibox)
{
    if (!minibox->tmp_node || minibox->tmp_node->content)
        return (NULL);    
    if(!validate_token(minibox->tmp_token, 0, WORD_TOKEN))
        return(NULL);    
    minibox->tmp_node->content = ft_strdup(minibox->tmp_token->value);
    minibox->tmp_token = minibox->tmp_token->next;
    token_list_main(minibox);
    return (minibox->tmp_node);
}
/* [token] <token list> */
static t_tree *token_list_case2(t_minibox *minibox)
{
    t_tree  *arg_node;

    if(!validate_token(minibox->tmp_token, 0, WORD_TOKEN))
        return(NULL);
    arg_node = ast_create_node(ARG_NODE);
    arg_node->content = ft_strdup(minibox->tmp_token->value);
    minibox->tmp_token = minibox->tmp_token->next;
    token_list_main(minibox);
    connect_subtree(&minibox->tmp_node, arg_node, RIGHT);
    return (arg_node);
}

/* <redir> <token list> */ 
static t_tree *token_list_case3(t_minibox *minibox)
{   
    t_tree  *redir_node;
    
    if(!validate_token(minibox->tmp_token, 0, RED_IN_TOKEN)
        && !validate_token(minibox->tmp_token, 0, RED_OUT_TOKEN))
        return(NULL);
    redir_node = redir_main(minibox);
    token_list_main (minibox);
    connect_subtree(&minibox->tmp_node, redir_node, LEFT);
    return (redir_node);
}
