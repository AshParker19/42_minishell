/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:24:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/06 15:46:04 by anshovah         ###   ########.fr       */
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

/* '<<' [file] */
static t_tree *redir_out_case1(t_minibox *minibox)
{
    t_tree  *red_out_ap_node;

    if(!validate_token(minibox->tmp_token, 0 , RED_OUT_TOKEN))
        return (NULL);
    if(!validate_token(minibox->tmp_token, 1 , RED_OUT_TOKEN))
        return (NULL);
    if(!validate_token(minibox->tmp_token, 2 , WORD_TOKEN))
        return(put_syntax_error(minibox, minibox->tmp_token->next->next));
    red_out_ap_node = ast_create_node(RED_OUT_AP);
    red_out_ap_node->content = ft_strdup(minibox->tmp_token->next->next->value);
    minibox->tmp_token = minibox->tmp_token->next->next->next;
    return (red_out_ap_node);
}

/* '<' [file] */
static t_tree *redir_out_case2(t_minibox *minibox)
{
    t_tree  *red_out_tr_node;
    
    if(!validate_token(minibox->tmp_token, 0, RED_OUT_TOKEN))
        return(NULL);
    if(!validate_token(minibox->tmp_token, 1, WORD_TOKEN))
        return(put_syntax_error(minibox, minibox->tmp_token->next));
    red_out_tr_node = ast_create_node(RED_OUT_TR);
    red_out_tr_node->content = ft_strdup(minibox->tmp_token->next->value);
    minibox->tmp_token = minibox->tmp_token->next->next;
    return (red_out_tr_node);
}
