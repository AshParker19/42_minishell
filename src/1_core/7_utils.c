/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:47 by astein            #+#    #+#             */
/*   Updated: 2024/01/07 12:54:31 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

t_bool	ft_isqoute(char c)
{
	return (c == '\'' || c == '"');
}

t_bool	ft_issep(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

t_bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\a'
		|| c == '\b' || c == '\f' || c == '\r');
}

/**
 * @brief	recursively traverses through the AST and counts the amount
 * 			of command nodes
 * 
 * @param	ast_node 
 * @return	int 
 */
int	cmd_counter(t_ast *ast_node)
{
	if (!ast_node)
		return (0);
	if (ast_node->type == CMD_NODE)
		return (1);
	return (1 + cmd_counter(ast_node->right));
}