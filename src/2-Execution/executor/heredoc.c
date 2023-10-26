/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/25 19:00:29 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief   a heredoc doesnt do var expansion for its input if the limiter
 *          contains any quotes!
 * 
 *          this function does two things:
 *              - it returns a bool regarding if there are any qoutes in the lim
 * 
 *          INPUT                   RETURN      ADUJSTED LIM
 *          Hello" World"           -> ft_true  -> Hello World
 *          Hello World             -> ft_false -> Hello World
 *          "He''o World"           -> ft_true  -> He''o World
 * 
 * @param str 
 * @return t_bool 
 */
static  t_bool check_qoutes(char *str)
{
    int qoute_state;
    t_bool  found_qoutes;
    int     i;
    i = -1;
    char *temp_lim;

    temp_lim =NULL;

    found_qoutes = ft_false;
    while (str[++i])
    {
        if (str[i] == '\'' || str[i] == '"')
            found_qoutes = ft_true;
        // copy form str to temp_lim
        // update the qoute state with updateqoute (think of add ? remove offset)
        // if qoutes are contextual just dont copy them to temp_lim
    }
    free(str);
    str = ft_strdup(temp_lim);
    free(temp_lim);
    return (found_qoutes);
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
int    heredoc(t_tree *redir_node, int *cmd_in_fd, char *line)
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
        expand_vars = check_qoutes(&delimiter); 
        while (true)
        {
            write (STDIN_FILENO, "> ", 2);
            line = get_next_line(STDIN_FILENO);
            if (ft_strcmp_strict(line, delimiter))
            {
                free (line);
                break ;
            }
            write (fd[P_LEFT], line, ft_strlen(line));
            free(line);
        }
        close (fd[P_LEFT]); // close because it was WRITE END
        free (delimiter);
        exit(0);
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
