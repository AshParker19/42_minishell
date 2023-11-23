/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:24:57 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/21 18:41:17 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*redir_in_case1(t_mbox *mbox);
static t_ast	*redir_in_case2(t_mbox *mbox);

/**
 * @brief   main function for redir in case
 *          
 * 			<redir in>     : '<<' [file]
 *			               | '<'  [file]
 *			               ;
 * 
 * @param   mbox 
 * @return  t_ast* 
 */
t_ast	*redir_in_main(t_mbox *mbox)
{
	t_ast	*red_in_node;
	t_token	*backup;

	backup = mbox->tmp_token;
	if (!mbox->tmp_token)
		return (NULL);
	red_in_node = redir_in_case1(mbox);
	if (red_in_node)
		return (red_in_node);
	mbox->tmp_token = backup;
	red_in_node = redir_in_case2(mbox);
	if (red_in_node)
		return (red_in_node);
	return (NULL);
}

/* '<<' [file] */
static t_ast	*redir_in_case1(t_mbox *mbox)
{
	t_ast	*red_in_hd_node;

	if (!validate_token(mbox->tmp_token, 0, RED_IN_TOKEN))
		return (NULL);
	if (!validate_token(mbox->tmp_token, 1, RED_IN_TOKEN))
		return (NULL);
	if (!validate_token(mbox->tmp_token, 2, WORD_TOKEN))
		return (create_syntax_err(mbox, mbox->tmp_token->next->next));
	red_in_hd_node = ast_create_node(RED_IN_HD);
	red_in_hd_node->content = ft_strdup(mbox->tmp_token->next->next->value);
	mbox->tmp_token = mbox->tmp_token->next->next->next;
	return (red_in_hd_node);
}

/* '<' [file]*/
static t_ast	*redir_in_case2(t_mbox *mbox)
{
	t_ast	*red_in_node;

	if (!validate_token(mbox->tmp_token, 0, RED_IN_TOKEN))
		return (NULL);
	if (!validate_token(mbox->tmp_token, 1, WORD_TOKEN))
		return (create_syntax_err(mbox, mbox->tmp_token->next));
	red_in_node = ast_create_node(RED_IN);
	red_in_node->content = ft_strdup(mbox->tmp_token->next->value);
	mbox->tmp_token = mbox->tmp_token->next->next;
	return (red_in_node);
}
