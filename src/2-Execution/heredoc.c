/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:00:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/13 14:17:28 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    heredoc(t_tree *redir_node, int *in_fd, char *line)
{
    char    *delimiter;
    int     fd[2];

    if (pipe(fd) < 0)
        exit (EXIT_FAILURE);
    *in_fd = fd[WRITE_END];
    delimiter = ft_strjoin(redir_node->content, "\n");
    while (true)
    {
        if (line)
            free (line);
        write (STDIN_FILENO, "> ", 2);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break ;
        if (ft_strcmp_strict(line, delimiter))
        {
            free (line);
            break ;
        }
        write (*in_fd, line, ft_strlen(line));
    }
    close (*in_fd); // close because it was WRITE END
    *in_fd = fd[READ_END]; // info was written to the reaad end and will be redirected later using dup2
    free (delimiter);
}
