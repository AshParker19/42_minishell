/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:26:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/02 18:29:19 by anshovah         ###   ########.fr       */
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
    return (new_node);
}

void    delete_ast(t_tree *root)
{
    if (root->left)
        delete_ast(root->left);
    if (root->right)
        delete_ast(root->right);
    if (root->content)
        free(root->content);
    free(root);
}

void    connect_subtree(t_tree **root, t_tree *node_to_add, int on_right)
{
    t_tree *tmp;

    tmp = NULL;
    if (!root || !*root || !node_to_add)
        return ;
    if (on_right)
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
	distance = 10;
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
		printf("type: %s, data: %s\n", type, root->content);
	else
		printf("type: %s\n", type);
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