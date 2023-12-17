/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:59:37 by astein            #+#    #+#             */
/*   Updated: 2023/12/17 18:42:38 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief   This file contains the functions that are used to display additional
 *			information druing runtime. It is used for debugging purposes.
 *			
 *			To enable info mode run the program with the -i flag.
 *
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#info-mode
 */

# include "frankenshell.h"

/**
 * @brief   Prints a simple colored line to the STDERR_FILENO like
 * 
 * 			|--------|
 * 
 * 			The width of the line is defined in config.h as `BANNER_WIDTH`
 * 
 * @param   border_symbol	used for the first and last character of the line
 * @param   mid_symbol  	use for the middle characters of the line
 * @param   clr        		color of the line
 * @param   app_new_line	whether to append an additional nl after the line
 */
static void	info_print_line(char border_symbol, char mid_symbol, char *clr, t_bool app_new_line)
{
	int	i;

	i = 0;
	dprintf(STDERR_FILENO, "%s", clr);
	dprintf(STDERR_FILENO, "%c", border_symbol);
	while (i++ < BANNER_WIDTH)
		dprintf(STDERR_FILENO, "%c", mid_symbol);
	dprintf(STDERR_FILENO, "%c", border_symbol);
	dprintf(STDERR_FILENO, "%s", RESET);
	dprintf(STDERR_FILENO, "\n");
	if (app_new_line)
		dprintf(STDERR_FILENO, "\n");
}

/**
 * @brief   Prints a string centerd to the STDERR_FILENO like
 * 
 * |                    INFO MODE ACTIVATED!                    |
 * 
 * @param   border_symbol	used for the first and last character of the line
 * @param   txt         
 * @param   free_it     
 * @param   clr         
 */
static void	info_put_text_center(char border_symbol, char *txt, t_bool free_it, char *clr)
{
	int	wordlen;
	int	i;

	if (!txt)
		return ;
	dprintf(STDERR_FILENO, "%s", clr);
	wordlen = ft_strlen(txt);
	dprintf(STDERR_FILENO, "%c", border_symbol);
	i = 0;
	while (i++ < (BANNER_WIDTH - wordlen) / 2)
		dprintf(STDERR_FILENO, " ");
	dprintf(STDERR_FILENO, "%s", txt);
	i = 0;
	while (i++ < (BANNER_WIDTH - wordlen) / 2)
		dprintf(STDERR_FILENO, " ");
	if (wordlen % 2 != 0)
		dprintf(STDERR_FILENO, " ");
	dprintf(STDERR_FILENO, "%c\n", border_symbol);
	if (free_it)
		free(txt);
	dprintf(STDERR_FILENO, "%s", RESET);
}

/**
 * @brief   to display the shifted input string in a readable way, this function
 * 			converts all the special characters to a readable format.
 * 
 * @param   s           
 * @return  char*       
 */
static char	*info_shift_readable(char *s)
{
	int		i;
	char	*readable;

	i = -1;
	readable = ft_strdup(s);
	while (readable[++i])
	{
		if (readable[i] == add_offset('\''))
			readable[i] = 'S';
		else if (readable[i] == add_offset('"'))
			readable[i] = 'D';
		else if (readable[i] == add_offset('|'))
			readable[i] = 'P';
		else if (readable[i] == add_offset('<'))
			readable[i] = 'I';
		else if (readable[i] == add_offset('>'))
			readable[i] = 'O';
		else if (readable[i] == NO_SPACE)
			readable[i] = 'X';
		else if (readable[i] == EMPTY_TOKEN)
			readable[i] = 'E';
	}
	return (readable);
}

/**
 * @brief   accepts an int 'type' and according to its value returns an
 * 			allocated node type string
 * 
 * @param   type        
 * @return  char*       
 */
static char	*get_node_type(int type)
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
 * @brief   recursively traverses through the 'ast' and:
 * 			puts a corresponding amount of spaces to make visible indentation
 * 			puts the node type according to the return value of 'get_node_type'
 * 
 * @param   ast         
 * @param   indent_level
 */
static void	display_ast(t_ast *ast, int indent_level)
{
	char	*type;
	int		distance;
	int		i;

	if (ast == NULL)
		return ;
	distance = 7;
	indent_level += distance;
	display_ast(ast->right, indent_level);
	type = get_node_type(ast->type);
	dprintf(STDERR_FILENO, "\n");
	i = distance;
	while (i < indent_level)
	{
		dprintf(STDERR_FILENO, " ");
		i++;
	}
	dprintf(STDERR_FILENO, "[%s] (%s)\n", type, ast->content);
	if (type)
		free(type);
	display_ast(ast->left, indent_level);
}

/**
 * @brief   If info_mode is activated it prints a banner using `info_print_line`
 * 			and `info_put_text_center` to STDERR_FILENO like
 * 
 *  ------------------------------------------------------------
 * |                    INFO MODE ACTIVATED!                    |
 *  ------------------------------------------------------------
 * 
 * @param   caption     
 * @param   data        
 * @param   clr         
 */
void	info_put_banner(t_mbox *mbox, char *caption, char *data, char *clr)
{
	if(!mbox->info_mode)
		return ;
	info_print_line(' ', '-', clr, ft_false);
	info_put_text_center('|', caption, ft_false, clr);
	info_put_text_center('|', data, ft_true, clr);
	info_print_line(' ', '-', clr, ft_false);
}

/**
 * @brief   If 'info_mode' is true prints one of a input state string to
 * 			STDERR_FILENO
 * 
 * @param   mbox        
 * @param   state       
 * @param   str         
 */
void	info_print_input_string(t_mbox *mbox, char *state, char *str, char *clr)
{
	char	*readable;

	if (!mbox->info_mode)
		return ;
	dprintf(STDERR_FILENO, "%s", clr);
	if (!ft_strcmp(state, "input original")
		|| !ft_strcmp(state, "input trimmed"))
		dprintf(STDERR_FILENO, "%s:\t\t\t(%s)\n\n", state, str);
	else
	{
		dprintf(STDERR_FILENO, "%s:\tshifted:\t(%s)\n", state, str);
		readable = info_shift_readable (str);
		dprintf(STDERR_FILENO, "\t\treadable:\t(%s)\n", readable);
		if (ft_strcmp(state, "input expanded"))
			dprintf(STDERR_FILENO, "\n");
		free(readable);
	}
	dprintf(STDERR_FILENO, "%s", RESET);
	if (!ft_strcmp(state, "input expanded"))
		info_print_line('=', '=', LIGHT_RED, ft_true);
}

/**
 * @brief   If 'info_mode' is true prints all the tokens in the 'tokens' ll
 * 
 * @param   mbox        
 */
void	info_print_tokenizer(t_mbox *mbox, char *clr)
{
	t_token	*current;

	if (!mbox->info_mode)
		return ;
	dprintf(STDERR_FILENO, "%s", clr);
	current = mbox->tokens;
	while (current)
	{
		dprintf(STDERR_FILENO, "type:(%d) \t token:(%s)\n", current->type, current->value);
		current = current->next;
	}
	info_print_line('=', '=', clr, ft_true);
	dprintf(STDERR_FILENO, "%s", RESET);
}

/**
 * @brief   If 'info_mode' is true creates and prints a visualisation of the
 * 			'ast' via 'display_ast'
 * 
 * @param   mbox        
 * @param   top_part    
 */
void	info_print_parser(t_mbox *mbox, char *clr)
{
	if (!mbox->info_mode)
		return ;
	dprintf(STDERR_FILENO, "%s", clr);
	display_ast(mbox->ast, 0);
	dprintf(STDERR_FILENO, "%s", RESET);
	info_print_line('=', '=', clr, ft_true);
}

/**
 * @brief	If 'info_mode' is true prints the executor banner
 * 
 * 			NOTE: the actuall execution output will be printed by the child
 * 					processes themselves
 *
 * @param	mbox
 * @param	top_part
 */
void	info_print_executor_banner(t_mbox *mbox, t_bool top_part, char *clr)
{
	char	*temp;

	if (!mbox->info_mode)
		return ;
	dprintf(STDERR_FILENO, "%s", clr);
	if (top_part)
	{
		temp = ft_itoa(cmd_counter(mbox->ast));
		if (!temp)
			return ;
		info_put_banner(mbox, "EXECUTOR",
			ft_strcat_multi(3, "(cmd count: ", temp, ")"), clr);
		free(temp);
	}
	else
		info_print_line('=', '=', clr, ft_true);
	dprintf(STDERR_FILENO, "%s", RESET);
}
