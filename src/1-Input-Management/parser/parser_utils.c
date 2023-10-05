/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:26:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/05 20:29:20 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_tree *ast_create_node(int node_type)
{
    t_tree *new_node;

    new_node = ft_calloc(1, sizeof(t_tree));
    if (!new_node)
        return (NULL);
    new_node->type = node_type;
	if(node_type == PIPE_NODE)
		new_node->content = ft_strdup("|");
	// else if(node_type == RED_IN )
	// 	new_node->content = ft_strdup("<");
	// else if(node_type == RED_OUT_TR)
	// 	new_node->content = ft_strdup(">");
	// else if(node_type == RED_IN_HD )
	// 	new_node->content = ft_strdup("<<");
	// else if(node_type == RED_OUT_AP)
	// 	new_node->content = ft_strdup(">>");
    return (new_node);
}

bool    validate_token(t_token *token, int next_amount, int token_type)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = token;
	if (!temp)
			return(false);
	while(i < next_amount)
	{
		temp = temp->next;
		if (!temp)
			return(false);
		i++;
	}
	if(!temp->value || temp->type != token_type)
		return(false);
	return(true);
}
/*
	When the parser finds an error it should print a message and end the parsing
	in a nice way.

	FIXME: ATM its using exit(0)
	TODO: ATM only for redir errors, maybe change it to all
			possible parser errors

	always returns null!
*/
void	*put_syntax_error(t_token *error_token)
{
	char    *err_msg;
	
	if(error_token && error_token->value)
	{
		err_msg = ft_strcat_multi(3,"syntax error near unexpected token `",
			error_token->value,"'");
		ft_putendl_fd (err_msg, 2);
		free(err_msg);
	}
	else
		ft_putendl_fd ("syntax error near unexpected token `newline'", 2);
	exit(0); //TODO: Replace the exit with a flag or some other shit
	//FIXME: free and exit from here somehow and destroy a tree
	// delete_ast(minibox->tmp_node); ????

	return(NULL);
}

void    delete_ast(t_tree *root)
{
	if(root)
	{
		if (root->left)
			delete_ast(root->left);
		if (root->right)
			delete_ast(root->right);
		if (root->content)
		{
			free(root->content);
			root->content = NULL;
		}
		free(root);
		root = NULL;
	}
}

void    connect_subtree(t_tree **root, t_tree *node_to_add, int side)
{
    t_tree *tmp;

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

static void	display_ast(t_tree *root, int indent_level)
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
void	print_parser_output(t_minibox *minibox)
{
	printf("\n ------------------------------------ \n");
	printf("|               PARSER               |\n");
	printf(" ------------------------------------ \n");
	display_ast(minibox->root, 0);
	printf(" ------------------------------------ \n");
}