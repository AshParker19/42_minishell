/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_hd_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:21:43 by astein            #+#    #+#             */
/*   Updated: 2023/12/18 19:52:12 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief   This file contains all the functions related to the execution of
 * 			the heredoc child process.
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#heredoc
 */

#include "frankenshell.h"

static void	exit_heredoc_child(t_mbox *mbox, t_hd *hd, int exit_status);

/**
 * @brief   A heredoc doesnt do var expansion for its input if the limiter
 *          contains any quotes!
 * 
 *          This function does two things:
 *              - it returns a bool regarding if there are any qoutes in the lim
 *              - changes str to the context quote free str
 * 
 *          To create the str without context qoutes a new str is generated
 *          copied char by char if the char is NOT a context qoute
 * 
 *          INPUT        	RETURN     		ADUJSTED LIM
 *          Hello World  	-> ft_true 		-> Hello World
 *          Hello" World"	-> ft_false		-> Hello World
 *          "He''o World"	-> ft_false		-> He''o World
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#heredoc
 * 
 * @param str 
 * @return t_bool 
 */
static t_bool	prepare_lim(char **str)
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
 * @brief	this function will be only called by 'hd_child' for each input line
 * 			of the heredoc. It will exit the child if recived:
 				CTRL+C or
 				CTRL+D
 * 
 * @param mbox 
 * @param hd 
 */
static void	hd_check_signal_exit(t_mbox *mbox, t_hd *hd)
{
	if (g_signal_status == SIGNAL_EXIT_HD)
		exit_heredoc_child(mbox, hd, 130);
	if (!hd->cur_line)
	{
		err_msg(mbox, NO_EXIT_STATUS, "nnynnn", ERR_P,
			W_HD, ft_itoa(mbox->count_cycles), DW, hd->lim, "')");
		exit_heredoc_child(mbox, hd, EXIT_SUCCESS);
	}
}

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
		temp = append_str(temp, get_var_value(mbox, key), ft_false);
	free (key);
	expanded_str = append_str(expanded_str, temp, ft_false);
	free (temp);
	return (expanded_str);
}

/**
 * @brief   This function will be called for each line that will be inserted
 *          into the heredoc. it's purpose is to look for dollar signs and
 *          expand all env. therefore it returns the expandend string
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
 * @param   mbox        
 * @param   str         
 * @return  char*       
 */
static char	*expand_heredoc_input(t_mbox *mbox, char *str)
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

/**
 * @brief   Will be called to properly exit the heredoc child process
 * 
 * @param   mbox        
 * @param   hd          
 * @param   exit_status 
 */
static void	exit_heredoc_child(t_mbox *mbox, t_hd *hd, int exit_status)
{
	close(hd->fd[P_LEFT]);
	free_whatever("pp", hd->lim, hd->cur_line);
	set_var_value_int(mbox, "?", exit_status);
	destroy_mbox(mbox);
}

/**
 * @brief   This is the main function to manage the heredoc child process
 * 
 * DOCUMENTATION:
 * https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#heredoc
 * 
 * @param   mbox        
 * @param   hd          
 * @param   cur_p       
 */
void	hd_child(t_mbox *mbox, t_hd hd, int *cur_p)
{
	t_bool	expand_vars;

	conf_sig_handler(SIG_STATE_HD_CHILD);
	expand_vars = prepare_lim(&hd.lim);
	close(hd.fd[P_RIGHT]);
	if (cur_p && cur_p[P_RIGHT] != -1)
		close(cur_p[P_RIGHT]);
	while (ft_true)
	{
		hd.cur_line = readline(HEREDOC_PROMPT);
		hd_check_signal_exit(mbox, &hd);
		if (hd.cur_line[0] != '\0')
		{
			if (str_cmp_strct(hd.cur_line, hd.lim))
				exit_heredoc_child(mbox, &hd, 0);
			if (expand_vars && hd.cur_line)
				hd.cur_line = expand_heredoc_input(mbox, hd.cur_line);
			ft_putendl_fd(hd.cur_line, hd.fd[P_LEFT]);
		}
		else
			ft_putendl_fd("", hd.fd[P_LEFT]);
		if (hd.cur_line)
			free(hd.cur_line);
	}
}
