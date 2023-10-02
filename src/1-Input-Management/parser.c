/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2023/10/02 13:32:12 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree *command(t_minibox *minibox);
t_tree *ast_add_node(int type);
void    delete_ast(t_tree *root);
void    connect_subtree(t_tree **root, t_tree *node_to_add, int on_right);
t_tree *token_list(t_minibox *minibox);
t_tree *token_list_case1(t_minibox *minibox);
t_tree *token_list_case2(t_minibox *minibox);

static void	display_ast(t_tree *root, int space)
{
	char	*type;
	int		code;
	int		distance;

	if (root == NULL)
		return ;
	distance = 10;
	space += distance;
	display_ast(root->right, space);
	code = root->type;
	// if (code == AST_AND)
	// 	type = ft_strdup("&&");
	if (code == ARG_NODE)
		type = ft_strdup("arg");
	else if (code == CMD_NODE)
		type = ft_strdup("cmd");
	// else if (code == AST_OR)
	// 	type = ft_strdup("||");
	// else if (code == AST_PIPE)
	// 	type = ft_strdup("|");
	// else if (code == AST_RED_AP)
	// 	type = ft_strdup(">>");
	// else if (code == AST_RED_HD)
	// 	type = ft_strdup("<<");
	// else if (code == AST_RED_IN)
	// 	type = ft_strdup("<");
	// else if (code == AST_RED_TR)
	// 	type = ft_strdup(">");
	// else if (code == AST_SEQ)
	// 	type = ft_strdup(";");
	printf("\n");
	for (int i = distance; i < space; i++)
		printf(" ");
	if (root->content)
		printf("type: %s, data: %s\n", type, root->content);
	else
		printf("type: %s\n", type);
	free(type);
	display_ast(root->left, space);
}

/* Print the ouput of the AST built by the Parser*/
void	print_parser_output(t_tree *root)
{
	printf("\n ------------------------------------ \n");
	printf("|               PARSER               |\n");
	printf(" ------------------------------------ \n");
	display_ast(root, 0);
	printf(" ------------------------------------ \n");
}

void	parse(t_minibox *minibox)
{
    minibox->tmp_token = minibox->tokens;
    command(minibox);
    //TODO:
}

t_tree *ast_add_node(int type)
{
    t_tree *new_node;

    new_node = ft_calloc(1, sizeof(t_tree));
    if (!new_node)
        return (NULL);
    new_node->type = type;
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
// ls -l -a
t_tree *command(t_minibox *minibox)
{
    t_tree  *cmd_node;

    cmd_node = ast_add_node(CMD_NODE);
    if (!cmd_node)
        return (NULL);
    minibox->tmp_node = cmd_node;
    token_list(minibox);
    if (cmd_node && !minibox->tmp_node->content)
    {
        delete_ast(minibox->tmp_node);
        return (NULL);
    }
    minibox->root = minibox->tmp_node;
    return cmd_node;
}

t_tree *token_list(t_minibox *minibox)
{
    t_tree  *tl_node;
    t_token *backup;

    backup = minibox->tmp_token;
    if (!minibox->tmp_token)
        return (NULL);
    tl_node = token_list_case1(minibox);
    if (tl_node)
        return (tl_node);
    minibox->tmp_token = backup;
    tl_node = token_list_case2(minibox);
    if (tl_node)
        return (tl_node);
    minibox->tmp_token = backup;
    //TODO: add a trhird case
    return (NULL);
}
// [name]  <token list>
t_tree *token_list_case1(t_minibox *minibox)
{
    // char    *name;

    if (minibox->tmp_node->content)
        return (NULL);
    if (minibox->tmp_token->type == TEXT_TOKEN) {
        minibox->tmp_node->content = ft_strdup(minibox->tmp_token->value);
        if (minibox->tmp_token)
            minibox->tmp_token = minibox->tmp_token->next;
        token_list(minibox);
        return (minibox->tmp_node);
    }
    return (NULL);
}
// [token] <token list>
t_tree *token_list_case2(t_minibox *minibox)
{
    // char    *arg;
    t_tree  *arg_node;

    if (minibox->tmp_token->type != TEXT_TOKEN)
        return (NULL);
    if (!minibox->tmp_token->value)
        return (NULL);
    arg_node = ast_add_node(ARG_NODE);
    arg_node->content = ft_strdup(minibox->tmp_token->value);
    if (minibox->tmp_token)
        minibox->tmp_token = minibox->tmp_token->next;
    printf("YO\n");
    token_list(minibox);
    connect_subtree(&minibox->tmp_node, arg_node, 1);
    return (arg_node);
}