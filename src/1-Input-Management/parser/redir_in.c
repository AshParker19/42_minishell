/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:24:57 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/05 18:54:54 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *redir_in_case1(t_minibox *minibox);
static t_tree *redir_in_case2(t_minibox *minibox);

t_tree *redir_in_main(t_minibox *minibox)
{
    t_tree  *red_in_node;
    t_token *backup;

    backup = minibox->tmp_token;
    if (!minibox->tmp_token)
        return (NULL);
    red_in_node = redir_in_case1(minibox);
    if (red_in_node)
        return (red_in_node);
    minibox->tmp_token = backup;
    red_in_node = redir_in_case2(minibox);
    if (red_in_node)
        return (red_in_node);
    return (NULL);
}
/* '<<' [file] */
static t_tree *redir_in_case1(t_minibox *minibox)
{
    t_tree  *red_in_hd_node;

    if (!validate_token(minibox->tmp_token, 0, RED_IN_TOKEN))
        return (NULL);
    if (!validate_token(minibox->tmp_token, 1, RED_IN_TOKEN))
        return (NULL);    
    if (!validate_token(minibox->tmp_token, 2, WORD_TOKEN))
        return(put_syntax_error(minibox->tmp_token->next->next));
    red_in_hd_node = ast_create_node(RED_IN_HD);
    red_in_hd_node->content = ft_strdup(minibox->tmp_token->next->next->value);
    minibox->tmp_token = minibox->tmp_token->next->next->next;
    return (red_in_hd_node);
}
/* '<' [file]*/
static t_tree *redir_in_case2(t_minibox *minibox)
{
    t_tree  *red_in_node;
    
    if(!validate_token(minibox->tmp_token, 0, RED_IN_TOKEN))
        return(NULL);
    if(!validate_token(minibox->tmp_token, 1, WORD_TOKEN))
        return(put_syntax_error(minibox->tmp_token->next));
    red_in_node = ast_create_node(RED_IN);
    red_in_node->content = ft_strdup(minibox->tmp_token->next->value);
    minibox->tmp_token = minibox->tmp_token->next->next;
    return (red_in_node);    
}


