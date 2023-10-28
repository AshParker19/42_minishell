/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:26:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/28 17:34:28 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

void	*put_syntax_error(t_mbox *mbox, t_token *error_token)
{
	char    *err_msg;
	
	if (mbox->error_status == ft_false)
	{
		mbox->error_status = ft_true;
		if(error_token && error_token->value)
		{
			err_msg = ft_strcat_multi(3,"syntax error near unexpected token `",
				error_token->value,"'");
			ft_putendl_fd (err_msg, 2);
			free(err_msg);
		}
		else
			ft_putendl_fd ("syntax error near unexpected token `newline'", 2);
	}
	if (error_token)
		mbox->tmp_token = error_token->next;
	return(NULL);
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

static void	display_ast(t_ast *root, int indent_level)
{
	char	*type;
	int		code;
	int		distance;

	if (root == NULL)
		return ;
	distance = 7;
	indent_level += distance;
	display_ast(root->right, indent_level);
	code = root->type;
	if (code == ARG_NODE)
		type = ft_strdup("arg");
	else if (code == CMD_NODE)
		type = ft_strdup("cmd");
	else if (code == PIPE_NODE)
		type = ft_strdup("|");
	else if (code == RED_OUT_AP)
		type = ft_strdup(">>");
	else if (code == RED_IN_HD)
		type = ft_strdup("<<");
	else if (code == RED_IN)
		type = ft_strdup("<");
	else if (code == RED_OUT_TR)
		type = ft_strdup(">");
	printf("\n");
	for (int i = distance; i < indent_level; i++)
		printf(" ");
	if (root->content)
		printf("[%s] (%s)\n", type, root->content);
	else
		printf("[%s]\n", type);
	free(type);
	display_ast(root->left, indent_level);
}

/* Print the ouput of the AST built by the Parser*/
void	print_parser_output(t_mbox *mbox)
{
	printf("\n ------------------------------------ \n");
	printf("|               PARSER               |\n");
	printf(" ------------------------------------ \n");
	display_ast(mbox->root, 0);
	printf(" ------------------------------------ \n\n");
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
