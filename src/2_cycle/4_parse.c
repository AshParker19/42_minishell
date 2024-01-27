/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:16:49 by astein            #+#    #+#             */
/*   Updated: 2024/01/06 19:29:49 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief	allocates a node for the AST and gives it a corresponding node type
 * 
 * @param	node_type 
 * @return	t_ast* 
 */
t_ast	*ast_create_node(int node_type)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = node_type;
	if (node_type == PIPE_NODE)
		new_node->content = ft_strdup("|");
	return (new_node);
}

t_bool	validate_token(t_token *token, int next_amount, int token_type)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = token;
	if (!temp)
		return (false);
	while (i < next_amount)
	{
		temp = temp->next;
		if (!temp)
			return (false);
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
 * @param ast 
 */
void	free_ast(t_ast *ast)
{
	if (ast)
	{
		free_ast(ast->left);
		free_ast(ast->right);
		if (ast->content)
		{
			free(ast->content);
			ast->content = NULL;
		}
		free(ast);
		ast = NULL;
	}
}

/**
 * @brief	
 * 
 * @param	ast 
 * @param	node_to_add 
 * @param	side 
 */
void	connect_subtree(t_ast **ast, t_ast *node_to_add, int side)
{
	t_ast	*tmp;

	tmp = NULL;
	if (!ast || !*ast || !node_to_add)
		return ;
	if (side == RIGHT)
	{
		if ((*ast)->right)
			tmp = (*ast)->right;
		(*ast)->right = node_to_add;
		node_to_add->right = tmp;
	}
	else
	{
		if ((*ast)->left)
			tmp = (*ast)->left;
		(*ast)->left = node_to_add;
		node_to_add->left = tmp;
	}
}

/**
 * @brief   takes the ll of tokens and tries to build an AST following this
 * 			BNF form:
 * 
 *			<job>          : <command> '|' <job>    
 *			               | <command>              
 *			               ;
 *
 *			<command>      : <token list>           
 *			               ;
 *
 *			<token list>   : [name]  <token list>   
 *			               | [arg]   <token list>   
 *			               | <redir> <token list>   
 *			               ;
 *
 *			<redir>        : <redir in> 
 *			               | <redir out>
 *			               ;
 *
 *			<redir in>     : '<<' [file]
 *			               | '<'  [file]
 *			               ;
 *
 *			<redir out>    : '>>' [file]
 *			               | '>'  [file]
 *			               ;
 * 			
 * 			this BNF form was taken from Gabriel Tocha
 * 			(https://github.com/portugueseTorch)
 * 			Thank you Gabriel for your help!
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/docs/documentation.md#parsing
 * 
 * @param   mbox 
 * @return  t_bool 
 */
t_bool	parse(t_mbox *mbox)
{
	info_put_banner(mbox, "PARSER", NULL, CYAN);
	mbox->tmp_token = mbox->tokens;
	mbox->ast = job_main(mbox);
	if (mbox->tmp_token)
		syntax_err_msg(mbox, mbox->tmp_token);
	info_print_parser(mbox, CYAN);
	if (mbox->syntax_err_encountered)
		return (ft_false);
	return (ft_true);
}
