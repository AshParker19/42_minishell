/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:04:05 by astein            #+#    #+#             */
/*   Updated: 2023/09/27 10:02:02 by anshovah         ###   ########.fr       */
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
# include "input_manager.h"
# include "executor.h"

/******************************************************************************/
/*    colors    */
# define GREEN 		"\033[0;32m"
# define RED 		"\033[0;31m"
# define YELLOW 	"\x1b[33m"
# define CYAN 		"\x1b[36m"
# define PURPLE 	"\x1b[35m"
# define RESET 		"\033[0m"
/******************************************************************************/
/* list of local variables */
typedef struct s_local_var t_local_var;

typedef struct s_minibox
{
    char        **env;
    char        *input_original;
    char        *input_trimmed;
    char        *input_quoted;
    char        *input_expanded;
    char        **global_vars;
    t_token     *tokens;
    t_tree      *root;
    t_local_var *local_vars;
}              t_minibox;

/* list of local variables (definition) */
typedef struct s_local_var
{
    char        *key;
    char        *value;
    struct      s_local_var *next;
}              t_local_var;
/******************************************************************************/

/* input_manager.c */
void	manage_input(t_minibox *minibox);

/* env.c */
char    *resolve_local_var(char *key);
void    store_local_var(t_minibox *minibox, char *key, char *value);
void    free_local_vars(t_minibox *minibox);

/* manage_minibox.c */
void	initialize_box(t_minibox *minibox, char **env);
void    free_input_strings(t_minibox *minibox);
void	free_matrix(t_minibox *minibox, int i);
void    free_and_close_box(t_minibox *minibox, int exit_status);

#endif
