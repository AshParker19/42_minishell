/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:02:16 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/22 09:53:58 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   a heredoc doesnt do var expansion for its input if the limiter
 *          contains any quotes!
 * 
 *          this function does two things:
 *              - it returns a bool regarding if there are any qoutes in the lim
 *              - changes str to the context qoute free str
 * 
 *          To create the str without context qoutes a new str is generated
 *          copied char by char if the char is NOT a context qoute
 * 
 *          INPUT                   RETURN      ADUJSTED LIM
 *          Hello" World"           -> ft_true  -> Hello World
 *          Hello World             -> ft_false -> Hello World
 *          "He''o World"           -> ft_true  -> He''o World
 * 
 * @param str 
 * @return t_bool 
 */
t_bool	check_lim_qoutes(char **str)
{
	t_bool	expand_vars;
	int		quote_state;
	int		old_quote_state;
	int		i;
	char	*temp_lim;

	expand_vars = ft_true;
	i = -1;
	temp_lim = NULL;
	quote_state = OUT_Q;
	while ((*str)[++i])
	{
		old_quote_state = quote_state;
		update_quote_state(&quote_state, add_offset((*str)[i]), ft_true);
		if ((*str)[i] == '\'' || (*str)[i] == '"')
			expand_vars = ft_false;
		if (old_quote_state == quote_state)
			temp_lim = append_str(temp_lim, ft_chr2str((*str)[i]), ft_true);
	}
	free(*str);
	*str = ft_strdup(temp_lim);
	free(temp_lim);
	return (expand_vars);
}


/**
 * @brief	This file deals with all heredoc related topics
 *			the only non static function 'heredoc' will be only called by
 *			'redirection.c'
 *			
 *			This file will perform 4 tasks:
 *				1. 'check_lim_qoutes'
 *					checks if there are any qoutes in the LIM if so it so
 *                  that 3. know if to expand
 *						- removes all contextual qoutes
 *				
 *				2. 'fork' - > 'heredoc_child'
 *					spawns a child process that will run until the LIM is found
 *					after writing all (expanded) lines into the FD we free the
 *					child and return to 'redirection.c'
 *				
 *				3.	(if the result of 1. is true)
 *					after each read line the var expansion will take place
 *					via 'expand_heredoc_input' and 'get_key'
 *
 *              4.  SIGNALS TODO:
 */

/* gets the value of expended vars inside of heredoc */
static	char	*tmp_buck(t_mbox *mbox, char *str, int *i, char *expanded_str)
{
	char	*key;
	char	*temp;

	temp = NULL;
	key = get_key(str, i);
	if (!key)
		temp = append_str(temp, "$", ft_false);
	else if (str_cmp_strct(key, "$"))
		temp = append_str(temp, key, ft_false);
	else
		temp = append_str(temp, get_var_value(mbox,
								key), ft_false);
	free (key);
	expanded_str = append_str(expanded_str, temp, ft_false);
	free (temp);
	return (expanded_str);
}

/**
 * @brief   this function will be called for each line that will be inserted
 *          into the heredoc. its purpose is to look for dollar signs and
 *          expand all env. therefore it returns the expandend string
 * 
 *          and frees the original one!
 * 
 *          EXAMPLES
 *              $           ->  $ 
 *              $ASD        ->  
 *              $"PATH"     ->  $"PATH"
 *              $LESS       ->  -R
 *              $ LESS      ->  $ LESS
 *              $?          ->  0   (last exit status)
 *              $$          ->  $$
 *              $$$LESS     ->  $$-R
 *
 * @param   str     
 * @return  char*   
 */
char	*expand_heredoc_input(t_mbox *mbox, char *str)
{
	int		i;
	t_bool	found_dollar;
	char	*expanded_str;

	i = -1;
	found_dollar = ft_false;
	expanded_str = NULL;
	while (str[++i])
	{
		if (!found_dollar && str[i] == '$')
			found_dollar = ft_true;
		else
		{
			if (found_dollar)
			{
				found_dollar = ft_false;
				expanded_str = tmp_buck(mbox, str, &i, expanded_str);
			}
			else
				expanded_str = append_str(expanded_str, ft_chr2str(str[i]),
						ft_true);
		}
	}
	free(str);
	return (expanded_str);
}
