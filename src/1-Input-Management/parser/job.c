/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:49:29 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/05 17:34:41 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_tree *job_case1(t_minibox *minibox);
static t_tree *job_case2(t_minibox *minibox);

t_tree *job_main(t_minibox *minibox)
{
    t_tree *job_node;
    t_token *backup;
    
    backup = minibox->tmp_token;
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

    
    // t_token *backup;
    // t_tree  *job_node;

    // backup = minibox->tmp_token;
    // job_node = ast_create_node(CMD_NODE);
    // if (!job_node)
    //     return (NULL);
    // // minibox->tmp_node = job_node;
    // job_node = job_case1(minibox);
    // if (job_node)
    // {
    //     if (!job_node->content)
    //     {
    //         delete_ast(minibox->tmp_node);
    //         return (NULL);
    //     }
    //     // minibox->root = minibox->tmp_node;
    //     return (job_node);
    // }
    // minibox->tmp_token = backup;
    // job_node = job_case2(minibox);
    // if (job_node)
    // {
    //     if (!job_node->content)
    //     {
    //         delete_ast(minibox->tmp_node);
    //         return (NULL);
    //     }
    //     // minibox->root = minibox->tmp_node;
    //     return (job_node);
    // }
    // return (NULL);      
}

/* <command> '|' <job> */
static t_tree *job_case1(t_minibox *minibox) //TODO: we need to check if there's something after pipe, do not treat
{
    t_tree *left;
    t_tree *pipe;
    t_tree *right;

    left = command_main(minibox);
    if(!left)
        return(NULL);
    if(!validate_token(minibox->tmp_token, 0, PIPE_TOKEN))
    {
        delete_ast(left);
        return(NULL);
    }
    pipe = ast_create_node(PIPE_NODE);
    if(!pipe)
    {
        delete_ast(left);
        return(NULL);
    }
    minibox->tmp_token = minibox->tmp_token->next;
    right = job_main(minibox);
    if(!right)
    {
        delete_ast(left);
        delete_ast(pipe);
        return(NULL);
    }
    pipe->left = left;
    pipe->right = right;
    return(pipe);
    
    // t_tree  *job_node;
    // t_tree  *pipe_node;
    // // int     pipe_index;

    // pipe_node = NULL;
    // if(!validate_token(minibox->tmp_token, 0, WORD_TOKEN))
    //     return(NULL);
    // if(!validate_token(minibox->tmp_token, 1, WORD_TOKEN)) // this check doesn't work for some reason
    //     return(NULL);    
    // job_node = command_main(minibox);
    // if (minibox->tmp_token)
    //     minibox->tmp_token = minibox->tmp_token->next; // here
    // if(!validate_token(minibox->tmp_token, 0, PIPE_TOKEN))
    //     return (NULL);
    // printf ("HERE\n");
    // // pipe_node = ast_create_node(PIPE_NODE);
    // // connect_subtree(&minibox->tmp_node, pipe_node, LEFT);
    // // connect_subtree(&minibox->tmp_node, job_node, LEFT);
    
    // return(job_node);
    // (void)minibox;
    // return (NULL);
}

static t_tree *job_case2(t_minibox *minibox) // call command_main instead
{
    t_tree  *job_node;

    job_node = command_main(minibox);
    if(job_node)
        printf("JOB NODE CREATED: %s\n",job_node->content);
    else
        printf("JOB NODE NOT CREATED\n");
    return (job_node);
}

