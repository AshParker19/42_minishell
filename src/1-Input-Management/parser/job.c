/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:49:29 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/27 15:13:16 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *job_case1(t_mbox *mbox);
static t_tree *job_case2(t_mbox *mbox);

t_tree *job_main(t_mbox *mbox)
{
    t_tree  *job_node;
    t_token *backup;
    
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
static t_tree *job_case1(t_mbox *mbox)
{
    t_tree *pipe;

    pipe = ast_create_node(PIPE_NODE);
    if(!pipe)
        return(NULL);
    pipe->left = command_main(mbox);
    if(!pipe->left)
    {
        delete_ast(pipe);
        return(NULL);
    }
    if(!validate_token(mbox->tmp_token, 0, PIPE_TOKEN))
    {
        delete_ast(pipe);
        return(NULL);
    }
    mbox->tmp_token = mbox->tmp_token->next;
    pipe->right = job_main(mbox);
    if(!pipe->right)
    {   
        delete_ast(pipe);
        return(NULL);
    }
    return(pipe);
}

/* command */
static t_tree *job_case2(t_mbox *mbox)
{
    t_tree  *job_node;

    job_node = command_main(mbox);
    return (job_node);
}

