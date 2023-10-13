/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/13 18:54:31 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    heredoc(t_tree *redir_node, int *cmd_in_fd, char *line)
{
    char    *delimiter;
    int     fd[2];

    if (pipe(fd) < 0)
        exit (EXIT_FAILURE);
    // *cmd_in_fd = fd[P_LEFT];
    delimiter = ft_strjoin(redir_node->content, "\n");
    while (true)
    {
        if (line)
            free (line);
        write (STDIN_FILENO, "> ", 2);
        line = get_next_line(STDIN_FILENO);
        if (ft_strcmp_strict(line, delimiter))
        {
            free (line);
            break ;
        }
        write (fd[P_LEFT], line, ft_strlen(line));
    }
    close (fd[P_LEFT]); // close because it was WRITE END
    *cmd_in_fd = fd[P_RIGHT]; // info was written to the reaad end and will be redirected later using dup2
    free (delimiter);
}
