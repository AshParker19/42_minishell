/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:11:12 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/08 02:27:17 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void put_text_center(char *txt, t_bool free_it)
{
	int wordlen;
	int i;
	
	if(!txt)
		return ;

	wordlen = ft_strlen(txt);
	printf("|");
	i = 0;
	while (i++ < (40-wordlen) / 2)
		printf(" ");
	printf("%s", txt);
	i = 0;
	while (i++ < (40-wordlen) / 2)
		printf(" ");
	if(wordlen % 2 != 0)
		printf(" ");
	printf("|\n");
	if (free_it)
		free(txt);
}

static void put_headline(char *caption, char *data, t_bool top_part)
{
	int count;
	int i;
	
	if (top_part)
	{
		printf(YELLOW" ");	
		i = 0;
		while (i++ < 40)
			printf("-");
		printf("\n");
		put_text_center(caption, ft_false);
		put_text_center(data, ft_true);
		i = 0;
		printf(" ");
		while (i++ < 40)
			printf("-");
		printf("\n"RESET);
	}
	else
	{
		printf(YELLOW " ");	
		i = 0;
		while (i++ < 40)
			printf("=");
		printf("\n\n"RESET);
	}
}

void	print_tokenizer_output(t_mbox *mbox)
{
	t_token *current;

	if (!mbox->print_info)
		return ;
	put_headline("TOKENIZER", NULL, ft_true);
	current = mbox->tokens;	
	while (current)	
	{	
		printf ("type:(%d) \t token:(%s)\n", current->type, current->value);	
		current = current->next;	
	}	
	put_headline("TOKENIZER", NULL, ft_false);
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
	printf("[%s] (%s)\n", type, root->content);
	free(type);
	display_ast(root->left, indent_level);
}

/* Print the ouput of the AST built by the Parser*/
void	print_parser_output(t_mbox *mbox, t_bool top_part)
{
	if (!mbox->print_info)
		return ;
	if(top_part)
		put_headline("PARSER", NULL, ft_true);
	else
	{
		display_ast(mbox->root, 0);
		put_headline(NULL, NULL, ft_false);
	}
}

void	print_executor_output(t_mbox *mbox, t_bool top_part)
{
	char	*temp;

	if (!mbox->print_info)
		return ;
	if(top_part)
	{
		temp = ft_itoa(cmd_counter(mbox->root));
		put_headline("EXECUTOR", ft_strcat_multi(3, "(cmd count: ",
			temp, ")"), ft_true);
		if(!temp)
			; // TODO: malloc error
		else
			free (temp);
	}
	else
		put_headline(NULL, NULL, ft_false);
}

void	display_string(t_mbox *mbox, char *state, char *str)
{
	if (!mbox->print_info)
		return ;
	if (!ft_strcmp(state, "input original"))
		put_headline("INPUT STATES", NULL, ft_true);	
	printf ("%s:\t(%s)\n", state, str);	
}

void delte_me(t_mbox *mbox, char *s)
{
    int i;
    char *c = ft_strdup(s);

    i=0;
	if (!mbox->print_info)
		return ;
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
    printf ("empty quotes:\t(%s)\n", c);
    free (c);
}