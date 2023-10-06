/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:49:29 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/06 10:22:17 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *job_case1(t_minibox *minibox);
static t_tree *job_case2(t_minibox *minibox);

t_tree *job_main(t_minibox *minibox)
{
    t_tree  *job_node;
    t_token *backup;
    
    backup = minibox->tmp_token; //TODO: Why?
    if (!minibox->tmp_token)
        return (NULL);
    job_node = job_case1(minibox);
    if (job_node)
        return (job_node);
    minibox->tmp_token = backup;
    job_node = job_case2(minibox);
    if (job_node)
        return (job_node);
    return (NULL);     
}

/* <command> '|' <job> */
static t_tree *job_case1(t_minibox *minibox)
{
    t_tree *pipe;

    pipe = ast_create_node(PIPE_NODE);
    if(!pipe)
        return(NULL);
    pipe->left = command_main(minibox);
    if(!pipe->left)
    {
        delete_ast(pipe);
        return(NULL);
    }
    if(!validate_token(minibox->tmp_token, 0, PIPE_TOKEN))
    {
        delete_ast(pipe);
        return(NULL);
    }
    minibox->tmp_token = minibox->tmp_token->next;
    pipe->right = job_main(minibox);
    if(!pipe->right)
    {   
        delete_ast(pipe);
        return(NULL);
    }
    return(pipe);
}

static t_tree *job_case2(t_minibox *minibox)
{
    t_tree  *job_node;

    job_node = command_main(minibox);
    return (job_node);
}

