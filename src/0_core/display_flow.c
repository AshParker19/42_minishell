/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:11:12 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/06 19:49:24 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	print_tokenizer_output(t_mbox *mbox)
{
	t_token *current;

	printf("\n ------------------------------------ \n");
	printf("|           TOKENIZER                |\n");
	printf(" ------------------------------------ \n");
	current = mbox->tokens;	
	while (current)	
	{	
		printf ("type:(%d) \t token:(%s)\n", current->type, current->value);	
		current = current->next;	
	}	
	printf(" ------------------------------------ \n");
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

/* Print the ouput of the AST built by the Parser*/
void	print_executor_output(t_mbox *mbox, int i)
{
    (void)mbox;
	if(i == 0)
	{
		printf("\n ------------------------------------ \n");
		printf("|              EXECUTOR              |\n");
		printf("|           cmd count: %d             |\n",cmd_counter(mbox->root));
		printf(" ------------------------------------ \n");	
	}
	else
		printf(" ------------------------------------ \n");
}

void delte_me(char *s)
{
    int i;
    char *c = ft_strdup(s);

    i=0;
    while (c[i])
    {
        if (c[i] == add_offset('\''))
            c[i] = '`';
        else if (c[i] == add_offset('"'))
            c[i] = 'D';
        else if (c[i] == add_offset('|'))
            c[i] = 'P';
        else if (c[i] == add_offset('<'))
            c[i] = 'I';
        else if (c[i] == add_offset('>'))
            c[i] = 'O';
        else if (c[i] == NO_SPACE)
            c[i] = '_';
        else if (c[i] == EMPTY_TOKEN)
            c[i] = 'E';
        i++;
    }
    printf ("empty quotes:\t\t(%s)\n", c);
    free (c);
}