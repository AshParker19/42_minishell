/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/18 15:19:11 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int    heredoc(t_tree *redir_node, int *cmd_in_fd, char *line)
{
    char    *delimiter;
    int     fd[2];
    int     status;

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
