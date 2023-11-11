/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flow2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:32:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/11 10:10:22 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_line(char symbol, char *clr, t_bool app_new_line)
{
	int i;

	i = 0;
	printf(" ");
	printf("%s", clr);
	while (i++ < 40)
		printf("%c", symbol);
	printf("%s", RESET);
	printf("\n");
	if (app_new_line)
		printf("\n");
}

/**
 * @brief	accepts an int 'type' and according to its value returns
 * 			an allocated node type string
 *
 * @param code
 * @return char*
 */
static char *get_node_type(int type)
{
	if (type == ARG_NODE)
		return (ft_strdup("arg"));
	else if (type == CMD_NODE)
		return (ft_strdup("cmd"));
	else if (type == PIPE_NODE)
		return (ft_strdup("|"));
	else if (type == RED_OUT_AP)
		return (ft_strdup(">>"));
	else if (type == RED_IN_HD)
		return (ft_strdup("<<"));
	else if (type == RED_IN)
		return (ft_strdup("<"));
	else if (type == RED_OUT_TR)
		return (ft_strdup(">"));
	return (NULL);
}

/**
 * @brief	recursively traverses through the 'ast' and:
 * 			puts a corresponding amount of spaces to make visible indentation
 * 			puts the node type according to the return value of 'get_node_type'
 *
 * @param	root
 * @param	indent_level
 */
static void display_ast(t_ast *root, int indent_level)
{
	char *type;
	int distance;
	int i;

	if (root == NULL)
		return;
	distance = 7;
	indent_level += distance;
	display_ast(root->right, indent_level);
	type = get_node_type(root->type);
	printf("\n");
	i = distance;
	while (i < indent_level)
	{
		printf(" ");
		i++;
	}
	printf("[%s] (%s)\n", type, root->content);
	if (type)
		free(type);
	display_ast(root->left, indent_level);
}

/**
 * @brief	if 'print_info' is true puts a header and dispays the contend
 * 			of each of the 'ast' nodes
 *
 */
void print_parser_output(t_mbox *mbox, t_bool top_part)
{
	if (!mbox->print_info)
		return;
	if (top_part)
		put_headline("PARSER", NULL, CYAN);
	else
	{
		display_ast(mbox->root, 0);
		print_line('=', CYAN, ft_true);
	}
}

/**
 * @brief	if 'print_info' is true puts a header
 *
 * @param	mbox
 * @param	top_part
 */
void print_executor_output(t_mbox *mbox, t_bool top_part)
{
	char *temp;

	if (!mbox->print_info)
		return;
	if (top_part)
	{
		temp = ft_itoa(cmd_counter(mbox->root));
		if (!temp)
			; // TODO: malloc error
		put_headline("EXECUTOR", ft_strcat_multi(3, "(cmd count: ", temp, ")"),
			GREEN);
		free(temp);
	}
	else
		print_line('=', GREEN, ft_true);
}
