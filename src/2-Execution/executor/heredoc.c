/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/26 19:46:32 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief   this function gets a string and should return a copied str of the
 *          key. the key will be returned.
 *          
 *          the index i will be shifted!
 * 
 * @param str 
 * @return char* 
 */
static  char *get_key(char *str, int *i)
{
    char    *key;

    key = NULL;
    if (!str)
        return (key);
    while(str[*i])
    {
        if (!key)
        {
            if (ft_isalpha(str[*i]) || str[*i]=='_')
                key = append_str(key, ft_chr2str(str[*i]), ft_true);
            else
            {
                (*i)--; //TODO: CHECK!
                return(ft_chr2str('$'));
            }
        }
        else
        {
            if (ft_isalnum(str[*i]) || str[*i]=='_')
                key = append_str(key, ft_chr2str(str[*i]), ft_true);
            else
            {
                (*i)--; //TODO: CHECK!
                return(key);
            }
        }
        (*i)++;
    }        
    return (key);
}



/**
 * @brief   this function will be called for each line that will be inserted
 *          into the heredoc. its purpose is to look for dollar signs and
 *          expand all vars. therefore it returns the expandend string
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
 *
 * @param   str     
 * @return  char*   
 */
static char   *expand_heredoc_input(t_minibox *minibox, char *str)
{
    int     i;
    t_bool  found_dollar;
    char    *expanded_str;
    char    *key;
    
    i = 0;
    found_dollar = ft_false;
    expanded_str = NULL;
    key = NULL;
    while (str[i])
    {
        // 1. look for dollar
        if (!found_dollar && str[i] == '$')
            found_dollar = ft_true;
        else
        {
            if (found_dollar)
            {
                found_dollar = ft_false;
                key = get_key(str, &i);
                if (ft_strcmp_strict(key, "$"))
                    expanded_str = append_str(expanded_str, key, ft_false);
                else
                {
                    printf("FOUND KEY IN HEREDOC!!! (%s)\n", key);
                    expanded_str = append_str(expanded_str, get_var_value(minibox, key), ft_false);
                    printf("expanded string (%s)\n", expanded_str);
                }
                free(key);
            }
            else
                expanded_str = append_str(expanded_str, ft_chr2str(str[i]), ft_true);
        }
        i++;
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
    int     quote_state;
    int     old_quote_state;
    t_bool  expand_vars;
    int     i;
    char    *temp_lim;
    char    cur_char;

    i = 0;
    temp_lim = NULL;
    old_quote_state = 0;
    quote_state = 0;
    expand_vars = ft_true;
    while ((*str)[i])
    {
        cur_char = (*str)[i];
        old_quote_state = quote_state;
        update_qoute_state(&quote_state, add_offset(cur_char));
        if (cur_char == '\'' || cur_char == '"')
            expand_vars = ft_false;
        if (old_quote_state == quote_state)
            temp_lim = append_str(temp_lim, ft_chr2str(cur_char), ft_true);
        i++;
    }
    free(*str);
    *str = ft_strdup(temp_lim);
    free(temp_lim);
    return (expand_vars);
}

// TODO: 
//  - deal with var expansion (if LIM isnt qouted)
//  - deal with \ as a flag for $ \ and ` to be ignored
//          so if inside the herdoc a is inputed b should remain
//              a               b
//              Hello\\World    Hello\World
//              Hello $LESS     Hello -R
//              Hello \$LESS    Hello $LESS
//              Hello `World
// 
//  if the var expansion turns out to be excatlly the lim str it still doesnt exit!
int    heredoc(t_minibox *minibox, t_tree *redir_node, int *cmd_in_fd, char *line)
{
    char    *delimiter;
    int     fd[2];
    int     status;
    t_bool  expand_vars;

    expand_vars = ft_false;

    // 1. check if it needs to do var expansion
    // 2. read until limiter (lim without qoutes!)
    // 3. do the expansion if nessesary
    
    if (pipe(fd) < 0)
        return (1);
    signal(SIGINT, SIG_IGN);
    int pid = fork();
    if (pid < 0)
        return (1);
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        close(fd[P_RIGHT]);
        delimiter = ft_strjoin(redir_node->content, "\n");
        expand_vars = check_lim_qoutes(&delimiter); 
        dprintf(2, "EXPAND VARS IN HEREDOC: %d\n", expand_vars);
        while (true) //TODO: kill myself
        {
            write (STDIN_FILENO, "> ", 2);
            line = get_next_line(STDIN_FILENO);
            if (ft_strcmp_strict(line, delimiter))
            {
                free (line);
                break ;
            }
            if (expand_vars && line)
                line = expand_heredoc_input(minibox, line);
            write (fd[P_LEFT], line, ft_strlen(line));
            free(line);
        }
        close (fd[P_LEFT]); // close because it was WRITE END
        free (delimiter);
        // TODO:
	    // not sure if this is correct here
	    // i need it for the heredoc...
	    if (minibox->executor.pid)
		    free( minibox->executor.pid);
        free_process(minibox);
        free_and_close_box(minibox, EXIT_SUCCESS);
    }
    close(fd[P_LEFT]);
    waitpid(pid, &status, 0);
    signal(SIGINT, SIG_DFL);
    if (WIFEXITED(status))
        status = WEXITSTATUS(status);
    else
        status = 1;
    if (status == 0)
        *cmd_in_fd = fd[P_RIGHT]; // info was written to the reaad end and will be redirected later using dup2
    return (status);
}