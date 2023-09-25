/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:05 by astein            #+#    #+#             */
/*   Updated: 2023/09/25 12:41:30 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* system includes */
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>


/* project includes */
# include "../libft/libft_printf.h"
# include "parsing.h"

/*    colors    */
# define GREEN 		"\033[0;32m"
# define RED 		"\033[0;31m"
# define YELLOW 	"\x1b[33m"
# define CYAN 		"\x1b[36m"
# define PURPLE 	"\x1b[35m"
# define RESET 		"\033[0m"

typedef struct s_minibox
{
    char        **env;
    char        *input;
    char        **vars;
    t_token     *tokens;
}              t_minibox;

// MAIN.C
int	main(int argc, char **argv, char** envp);


// SIGNALS.C


// BUILTINS
// 


#endif
