/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:50:45 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/15 14:16:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

static t_ast	*redir_case1(t_mbox *mbox);
static t_ast	*redir_case2(t_mbox *mbox);

/**
 * @brief   main function for redir case
 *          
 * 			<redir>        : <redir in> 
 *			               | <redir out>
 *			               ;
 * 
 * @param   mbox 
 * @return  t_ast* 
 */
t_ast	*redir_main(t_mbox *mbox)
{
	t_ast	*redir_node;
	t_token	*backup;

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
static t_ast	*redir_case1(t_mbox *mbox)
{
	t_ast	*redir_in_node;

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
static t_ast	*redir_case2(t_mbox *mbox)
{
	t_ast	*redir_out_node;

	if (!mbox->tmp_token)
		return (NULL);
	if (mbox->tmp_token->type != RED_OUT_TOKEN)
		return (NULL);
	if (!mbox->tmp_token->value)
		return (NULL);
	redir_out_node = redir_out_main(mbox);
	return (redir_out_node);
}
