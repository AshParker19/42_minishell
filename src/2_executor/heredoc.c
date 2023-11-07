/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/11/07 18:26:10 by anshovah         ###   ########.fr       */
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


/**
 * @brief   this function will be called for each line that will be inserted
 *          into the heredoc. its purpose is to look for dollar signs and
 *          expand all env_vars. therefore it returns the expandend string
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
static char   *expand_heredoc_input(t_mbox *mbox, char *str)
{
    int     i;
    t_bool  found_dollar;
    char    *expanded_str;
    char    *key;
    
    i = -1;
    found_dollar = ft_false;
    expanded_str = NULL;
    key = NULL;
    while (str[++i])
    {
        if (!found_dollar && str[i] == '$')
            found_dollar = ft_true;
        else
        {
            if (found_dollar)
            {
                found_dollar = ft_false;
                key = get_key(mbox, str, &i);
                if (!key)
                    expanded_str = append_str(expanded_str, "$", ft_false);
                else if (str_cmp_strct(key, "$"))
                    expanded_str = append_str(expanded_str, key, ft_false);
                else
                    expanded_str = append_str(expanded_str, get_var_value(mbox, key), ft_false);
                free(key);
            }
            else
                expanded_str = append_str(expanded_str, ft_chr2str(str[i]), ft_true);
        }
    }
    free (str);
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
static  t_bool check_lim_qoutes(char **str)
{
    t_bool  expand_vars;
    int     quote_state;
    int     old_quote_state;
    int     i;
    char    *temp_lim;

    expand_vars = ft_true;
    i = -1;
    temp_lim = NULL;
    quote_state = OUT_Q;
    while ((*str)[++i])
    {
        old_quote_state = quote_state;
        update_qoute_state(&quote_state, add_offset((*str)[i]), ft_true);
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

static  void exit_heredoc_child(t_mbox *mbox, int *fd, char *delimiter)
{
    close (fd[P_LEFT]); // close because it was WRITE END
    free (delimiter);
    close_process_fds_v2(mbox);
    free_and_close_box_v2(mbox);
}

static  void heredoc_child(t_mbox *mbox, int *fd, char *delimiter)
{
    char    *cur_line;
    t_bool  expand_vars;
    
    close(fd[P_RIGHT]);
    update_signals(SIGNAL_HEREDOC);
    delimiter = ft_strjoin(delimiter, "\n");
    expand_vars = check_lim_qoutes(&delimiter); 
    while (true)
    {
        write (STDIN_FILENO, "> ", 2);
        cur_line = get_next_line(STDIN_FILENO);
        if (!cur_line)
        {
            create_err_msg("nnynyn", ERR_PROMT, "warning: here-document at line ", ft_itoa(mbox->count_cycles), " delimited by end-of-file (wanted `", ft_strtrim(delimiter, "\n"), "')");
            exit_heredoc_child(mbox, fd, delimiter);
        }
        if (str_cmp_strct(cur_line, delimiter))
        {
            free (cur_line);
            break ;
        }
        if (expand_vars && cur_line)
            cur_line = expand_heredoc_input(mbox, cur_line);
        write (fd[P_LEFT], cur_line, ft_strlen(cur_line));
        free(cur_line);
    }
    exit_heredoc_child(mbox, fd, delimiter);
}

// TODO: 
//  - deal with var expansion (if LIM isnt qouted)
//  if the var expansion turns out to be excatlly the lim str it still doesnt exit!
int    heredoc(t_mbox *mbox, t_ast *redir_node, int *cmd_in_fd)
{
    int     fd[2];
    int     status;

    if (pipe(fd) < 0)
        err_free_and_close_box(mbox);
    update_signals(SIGNAL_PARENT);
    int pid = fork();
    if (pid < 0)
        err_free_and_close_box(mbox);
    if (pid == 0)
    {
        dprintf (2, "HEREDOC PID %d\n", getpid());
        heredoc_child(mbox, fd, redir_node->content);
    }
    close(fd[P_LEFT]);
    waitpid(pid, &status, 0);
    update_signals(SIGNAL_CHILD);
    if (WIFEXITED(status))
        status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        status = WTERMSIG(status) + 128;
        dprintf (2, "DDDDDDDDDDDDDDDDDDDDDDDDDDDD\nPID %d\n", getpid());
    }
    else
        status = 1;
    if (status == 0)
        *cmd_in_fd = fd[P_RIGHT]; // info was written to the reaad end and will be redirected later using dup2
    return (status); //TODO:
}
