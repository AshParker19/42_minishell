/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:26:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/06 15:01:54 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief	allocates a node for the AST and gives it a corresponding node type
 * 
 * @param	node_type 
 * @return	t_ast* 
 */
t_ast *ast_create_node(int node_type)
{
    t_ast *new_node;

    new_node = ft_calloc(1, sizeof(t_ast));
    if (!new_node)
        return (NULL);
    new_node->type = node_type;
	if (node_type == PIPE_NODE)
		new_node->content = ft_strdup("|");
    return (new_node);
}

/**
 * @brief	??????????????????????
 * 
 * @param	token 
 * @param	next_amount 
 * @param	token_type 
 * @return	t_bool 
 */
t_bool    validate_token(t_token *token, int next_amount, int token_type)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = token;
	if (!temp)
			return(false);
	while( i < next_amount)
	{
		temp = temp->next;
		if (!temp)
			return(false);
		i++;
	}
	if (!temp->value || temp->type != token_type)
		return (false);
	return (true);
}



/**
 * @brief	recursively traverses trough the tree:
 * 				- frees all content of the nodes
 * 				- the nodes themselves
 * 
 * 			NOTE: function should only be called by 'free_cycle'
 * @param root 
 */
void    free_ast_v2(t_ast *root)
{
	if(root)
	{
		if (root->left)
			free_ast_v2(root->left);
		if (root->right)
			free_ast_v2(root->right);
		if (root->content)
		{
			free(root->content);
			root->content = NULL;
		}
		free(root);
		root = NULL;
	}
}
/**
 * @brief	
 * 
 * @param	root 
 * @param	node_to_add 
 * @param	side 
 */
void    connect_subtree(t_ast **root, t_ast *node_to_add, int side)
{
    t_ast *tmp;

    tmp = NULL;
    if (!root || !*root || !node_to_add)
        return ;
    if (side == RIGHT)
    {
        if ((*root)->right)
            tmp = (*root)->right;
        (*root)->right = node_to_add;
        node_to_add->right = tmp;
    }
    else
    {
        if ((*root)->left)
            tmp = (*root)->left;
        (*root)->left = node_to_add;
        node_to_add->left = tmp;
    }
}

/**
 * @brief	this function frees and NULLs all 4 input strings, if they have
 * 			been allocated before
 * 
 * 			NOTE: function should only be called by 'free_cycle'
 * 
 * @param mbox 
 */
void free_input_strings_v2(t_mbox *mbox)
{
	if (mbox->inp_orig)
	{
		free(mbox->inp_orig);
		mbox->inp_orig = NULL;
	}
	if (mbox->inp_trim)
	{
		free(mbox->inp_trim);
		mbox->inp_trim = NULL;
	}
	if (mbox->inp_shift)
	{
		free (mbox->inp_shift);
		mbox->inp_shift = NULL;
	}
	if (mbox->inp_expand)
	{
		free(mbox->inp_expand);
		mbox->inp_expand = NULL;
	}
}
