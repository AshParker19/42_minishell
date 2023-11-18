/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/18 16:25:47 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
static t_bool	check_lim_qoutes(char **str)
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

static void	heredoc_child(t_mbox *mbox, int *fd, char *lim)
{
	char	*cur_line;
	t_bool	expand_vars;

	close(fd[P_RIGHT]);
	update_signals(SIGNAL_HEREDOC);
	lim = ft_strdup(lim);
	expand_vars = check_lim_qoutes(&lim);
	mbox->stop_heredoc = ft_false;
	while (FRANCENDOC_ECHOES_IN_ETERNITY)
	{
		cur_line = readline(HEREDOC_PROMPT);
		if (mbox->stop_heredoc == ft_true)
			exit_heredoc_child(mbox, fd, lim, cur_line);
		check_ctrl_d(mbox, fd, lim, cur_line);
		if(cur_line[0] != '\0')
		{
			if (str_cmp_strct(cur_line, lim))
				exit_heredoc_child(mbox, fd, lim, cur_line);
			if (expand_vars && cur_line)
				cur_line = expand_heredoc_input(mbox, cur_line);
			ft_putendl_fd(cur_line, fd[P_LEFT]);	
		}
		else
			ft_putendl_fd("", fd[P_LEFT]);	
		if (cur_line)
			free(cur_line);
	}
}

// TODO:
//  - deal with var expansion (if LIM isnt qouted)
//  if the var expansion turns out to be excatlly the lim str it still doesnt exit!
t_bool	heredoc(t_mbox *mbox, t_ast *redir_node, int *cmd_in_fd)
{
	int		fd[2];
	int		exit_status;
	char	*exit_status_str;
	int		pid_hd;

	if (pipe(fd) < 0)
		err_free_and_close_box(mbox, EXIT_FAILURE);
	update_signals(SIGNAL_PARENT);
	pid_hd = fork();
	if (pid_hd < 0)
		err_free_and_close_box(mbox, EXIT_FAILURE);
	if (pid_hd == 0)
		heredoc_child(mbox, fd, redir_node->content);
	close(fd[P_LEFT]);
	waitpid(pid_hd, &exit_status, 0);
	update_signals(SIGNAL_CHILD);
	if (exit_status != EXIT_SUCCESS)
	{
		set_var_value_int(mbox, "?", exit_status);
		return (ft_false);
	}
	else
	{
		*cmd_in_fd = fd[P_RIGHT];
		return (ft_true);
	}
	
	// if (WIFEXITED(exit_status))
	// 	exit_status = WEXITSTATUS(exit_status);
	// else if (WIFSIGNALED(exit_status))
	// {
	// 	exit_status = WTERMSIG(exit_status) + 128;
	// 	dprintf(2, "DDDDDDDDDDDDDDDDDDDDDDDDDDDD\nPID %d\n", getpid());
	// }
	// else
	// 	exit_status = 1;
			// info was written to the reaad end and will be redirected later using dup2
	// close(fd[P_RIGHT]);



	// FIX 10.11. 18:45 uncomment later maybe
	// exit_status_str = ft_itoa(exit_status);
	// set_var_value(mbox, "?", exit_status_str);
	// // dprintf(2, "{%s}{%s}\n", exit_status_str, get_var_value(mbox, "?"));
	// free(exit_status_str);
}
