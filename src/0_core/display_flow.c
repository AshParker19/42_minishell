/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:11:12 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/08 13:05:58 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief	printf the middle line of the header
 * 			calculates the length of 'txt' and according to that value
 * 			prints the needed amount of spaces so the printed text will be 
 * 			centered in the middle of the line
 * 
 * @param	txt 
 * @param	free_it 
 */
static void put_text_center(char *txt, t_bool free_it)
{
	int wordlen;
	int i;
	
	if (!txt)
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

/**
 * @brief	prints header
 * 			the firts and the last lines consist only of '-'
 * 			on the middle one prints 'caption' centered by 'put_text_center'
 * 			if 'data' is not NULL
 * 				one more line with some info will be put after 'caption' line
 * 
 * @param	caption 
 * @param	data 
 * @param	top_part 
 * @param	i 
 */
void	put_headline(char *caption, char *data, t_bool top_part, int i)
{
	int count;
	
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

/**
 * @brief	if 'print_info' is true printf one of a input state string
 * 			if it's 'original string' puts the header for all the input
 * 			strings too
 * 
 * @param	mbox 
 * @param	state 
 * @param	str 
 */
void	display_string(t_mbox *mbox, char *state, char *str)
{
	if (!mbox->print_info)
		return ;
	if (!ft_strcmp(state, "input original"))
		put_headline("INPUT STATES", NULL, ft_true, 0);	
	printf ("%s:\t(%s)\n", state, str);	
}

void delte_me(t_mbox *mbox, char *s, int i)
{
    char	*c;

	if (!mbox->print_info)
		return ;
	c = ft_strdup(s);
    while (c[++i])
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
    }
    printf ("empty quotes:\t(%s)\n", c);
    free (c);
}

/**
 * @brief	if 'print_info' is true puts a header and prints the content 
 * 			of each of the 'tokens' ll nodes
 * 
 * @param	mbox 
 */
void	print_tokenizer_output(t_mbox *mbox)
{
	t_token *current;

	if (!mbox->print_info)
		return ;
	put_headline("TOKENIZER", NULL, ft_true, 0);
	current = mbox->tokens;	
	while (current)	
	{	
		printf ("type:(%d) \t token:(%s)\n", current->type, current->value);	
		current = current->next;	
	}	
	put_headline("TOKENIZER", NULL, ft_false, 0);
}

