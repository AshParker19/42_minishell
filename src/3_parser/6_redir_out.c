/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:24:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/19 02:08:50 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

static t_ast	*redir_out_case1(t_mbox *mbox);
static t_ast	*redir_out_case2(t_mbox *mbox);

/**
 * @brief   main function for redir out case
 *          
 * 			<redir out>    : '>>' [file]
 *			               | '>'  [file]
 *			               ;
 * 
 * @param   mbox 
 * @return  t_ast* 
 */
t_ast	*redir_out_main(t_mbox *mbox)
{
	t_ast	*red_out_node;
	t_token	*backup;

	backup = mbox->tmp_token;
	if (!mbox->tmp_token)
		return (NULL);
	red_out_node = redir_out_case1(mbox);
	if (red_out_node)
		return (red_out_node);
	mbox->tmp_token = backup;
	red_out_node = redir_out_case2(mbox);
	if (red_out_node)
		return (red_out_node);
	return (NULL);
}

/* '>>' [file] */
static t_ast	*redir_out_case1(t_mbox *mbox)
{
	t_ast	*red_out_ap_node;

	if (!validate_token(mbox->tmp_token, 0, RED_OUT_TOKEN))
		return (NULL);
	if (!validate_token(mbox->tmp_token, 1, RED_OUT_TOKEN))
		return (NULL);
	if (!validate_token(mbox->tmp_token, 2, WORD_TOKEN))
		return (syntax_err_msg(mbox, mbox->tmp_token->next->next));
	red_out_ap_node = ast_create_node(RED_OUT_AP);
	red_out_ap_node->content = ft_strdup(mbox->tmp_token->next->next->value);
	mbox->tmp_token = mbox->tmp_token->next->next->next;
	return (red_out_ap_node);
}

/* '>' [file] */
static t_ast	*redir_out_case2(t_mbox *mbox)
{
	t_ast	*red_out_tr_node;

	if (!validate_token(mbox->tmp_token, 0, RED_OUT_TOKEN))
		return (NULL);
	if (!validate_token(mbox->tmp_token, 1, WORD_TOKEN))
		return (syntax_err_msg(mbox, mbox->tmp_token->next));
	red_out_tr_node = ast_create_node(RED_OUT_TR);
	red_out_tr_node->content = ft_strdup(mbox->tmp_token->next->value);
	mbox->tmp_token = mbox->tmp_token->next->next;
	return (red_out_tr_node);
}
