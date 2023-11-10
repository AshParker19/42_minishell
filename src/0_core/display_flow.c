/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:11:12 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/10 12:30:26 by astein           ###   ########.fr       */
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
static void put_text_center(char *txt, t_bool free_it, char *clr)
{
	int wordlen;
	int i;
	
	printf("%s", clr);
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
	printf("%s", RESET);
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
void	put_headline(char *caption, char *data, t_bool top_part, char *clr)
{
	if (top_part)
	{
		print_line('-', clr);
		put_text_center(caption, ft_false, clr);
		put_text_center(data, ft_true, clr);
		print_line('-', clr);
		printf("\n"RESET);
	}
	else
	{
		print_line('=', clr);
		printf("\n"RESET);
	}
}

static char *shift_readable(char *s)
{
	int 	i;
    char	*readable;
	
	i = -1;
	readable = ft_strdup(s);
    while (readable[++i])
    {
        if (readable[i] == add_offset('\''))
            readable[i] = '`';
        else if (readable[i] == add_offset('"'))
            readable[i] = 'D';
        else if (readable[i] == add_offset('|'))
            readable[i] = 'P';
        else if (readable[i] == add_offset('<'))
            readable[i] = 'I';
        else if (readable[i] == add_offset('>'))
            readable[i] = 'O';
        else if (readable[i] == NO_SPACE)
            readable[i] = '_';
        else if (readable[i] == EMPTY_TOKEN)
            readable[i] = 'E';
    }
	return (readable);
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
void	display_info_str(t_mbox *mbox, char *state, char *str)
{
	char *readable;
	
	if (!mbox->print_info)
		return ;
	if (!ft_strcmp(state, "input original"))
	{
		printf ("\n");
		put_headline("INPUT STATES", NULL, ft_true, YELLOW);	
	}
	if (!ft_strcmp(state, "input original") ||
		!ft_strcmp(state, "input trimmed"))
		printf ("%s:\t\t\t(%s)\n\n", state, str);	
	else
	{
		printf ("%s:\tshifted:\t(%s)\n", state, str);
		readable = shift_readable (str);
		printf ("\t\treadable:\t(%s)\n\n", readable);	
		free(readable);
	}
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
	put_headline("TOKENIZER", NULL, ft_true, YELLOW);
	current = mbox->tokens;	
	while (current)	
	{	
		printf ("type:(%d) \t token:(%s)\n", current->type, current->value);	
		current = current->next;	
	}	
	put_headline("TOKENIZER", NULL, ft_false, YELLOW);
}

