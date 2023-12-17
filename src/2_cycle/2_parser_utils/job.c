/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:49:29 by anshovah          #+#    #+#             */
/*   Updated: 2023/12/15 14:16:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

static t_ast	*job_case1(t_mbox *mbox);
static t_ast	*job_case2(t_mbox *mbox);

/**
 * @brief   main function for job case
 * 			
 * 			<job>          : <command> '|' <job>    
 *			               | <command>              
 *			               ;
 
 * @param   mbox 
 * @return  t_ast* 
 */
t_ast	*job_main(t_mbox *mbox)
{
	t_ast	*job_node;
	t_token	*backup;

	if (!mbox->tmp_token)
		return (NULL);
	backup = mbox->tmp_token;
	job_node = job_case1(mbox);
	if (job_node)
		return (job_node);
	mbox->tmp_token = backup;
	job_node = job_case2(mbox);
	if (job_node)
		return (job_node);
	return (NULL);
}

/* <command> '|' <job> */
static t_ast	*job_case1(t_mbox *mbox)
{
	t_ast	*pipe;

	pipe = ast_create_node(PIPE_NODE);
	if (!pipe)
		return (NULL);
	pipe->left = command_main(mbox);
	if (!pipe->left)
	{
		free_ast_v2(pipe);
		return (NULL);
	}
	if (!validate_token(mbox->tmp_token, 0, PIPE_TOKEN))
	{
		free_ast_v2(pipe);
		return (NULL);
	}
	mbox->tmp_token = mbox->tmp_token->next;
	pipe->right = job_main(mbox);
	if (!pipe->right)
	{
		free_ast_v2(pipe);
		return (NULL);
	}
	return (pipe);
}

/* command */
static t_ast	*job_case2(t_mbox *mbox)
{
	t_ast	*job_node;

	job_node = command_main(mbox);
	return (job_node);
}
