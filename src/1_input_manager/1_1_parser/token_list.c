/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:29 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/15 14:16:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

static t_ast	*token_list_case1(t_mbox *mbox);
static t_ast	*token_list_case2(t_mbox *mbox);
static t_ast	*token_list_case3(t_mbox *mbox);

/**
 * @brief   main function for token list case
 *          
 * 			<token list>   : [name]  <token list>   
 *			               | [arg]   <token list>   
 *			               | <redir> <token list>   
 *			               ;
 * 
 * @param   mbox 
 */
void	token_list_main(t_mbox *mbox)
{
	t_ast	*tl_node;
	t_token	*backup;

	backup = mbox->tmp_token;
	if (!mbox->tmp_token)
		return ;
	tl_node = token_list_case1(mbox);
	if (tl_node)
		return ;
	mbox->tmp_token = backup;
	tl_node = token_list_case2(mbox);
	if (tl_node)
		return ;
	mbox->tmp_token = backup;
	tl_node = token_list_case3(mbox);
}

/* [name]  <token list> */
static t_ast	*token_list_case1(t_mbox *mbox)
{
	if (!mbox->tmp_node || mbox->tmp_node->content)
		return (NULL);
	if (!validate_token(mbox->tmp_token, 0, WORD_TOKEN))
		return (NULL);
	mbox->tmp_node->content = ft_strdup(mbox->tmp_token->value);
	mbox->tmp_token = mbox->tmp_token->next;
	token_list_main(mbox);
	return (mbox->tmp_node);
}

/* [token] <token list> */
static t_ast	*token_list_case2(t_mbox *mbox)
{
	t_ast	*arg_node;

	if (!validate_token(mbox->tmp_token, 0, WORD_TOKEN))
		return (NULL);
	arg_node = ast_create_node(ARG_NODE);
	arg_node->content = ft_strdup(mbox->tmp_token->value);
	mbox->tmp_token = mbox->tmp_token->next;
	token_list_main(mbox);
	connect_subtree(&mbox->tmp_node, arg_node, RIGHT);
	return (arg_node);
}

/* <redir> <token list> */ 
static t_ast	*token_list_case3(t_mbox *mbox)
{
	t_ast	*redir_node;

	if (!validate_token(mbox->tmp_token, 0, RED_IN_TOKEN)
		&& !validate_token(mbox->tmp_token, 0, RED_OUT_TOKEN))
		return (NULL);
	redir_node = redir_main(mbox);
	if (!redir_node)
		return (NULL);
	token_list_main (mbox);
	connect_subtree (&mbox->tmp_node, redir_node, LEFT);
	return (redir_node);
}
