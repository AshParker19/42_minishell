/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:31 by astein            #+#    #+#             */
/*   Updated: 2023/10/28 15:57:45 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void change_pwd(t_mbox *mbox, char *new_path)
{
    set_var_value(mbox, "OLDPWD", ft_strdup(get_var_value(mbox, "PWD")));
    chdir(new_path);
    set_var_value(mbox, "PWD", ft_strdup(getcwd(NULL, 0)));
}
/**
 * 	CD =============================
 * 
 * 	No args				->	cd to home				DONE
 * 	Empty args			->	do nothing				DONE
 *  Args 				->	cd to arg				DONE
 *	Args.Arg not found	->	error					NOT SIMILAR
 * 	
 * 
 *  HOME not set		->	"~" Doesn't work & no args does nothing
 * 	PWD/OLDPWD not set	->	everything works normally when changing
 * 							directories always updates PWD/OLDPWD
 *  
 *	ATM OLDPWD is not being updated
    UPDATE PWD in ENV?

    doenst matter if it ends on / or not
    cd Documents/../../astein/Downloads/../../../../../../
    cd Documents/../../astein/Downloads/../../../../../..

*/
void	builtin_cd(t_mbox *mbox, t_ast *arg_node)
{
    struct stat path_stat;

    if (!arg_node)
        change_pwd(mbox, get_var_value(mbox, "HOME"));
    else if (arg_node->right)
        create_error_msg("nn", ERR_PROMT, "cd: too many arguments");
    else
    {
        // Check if it's a valid directory
        if (stat(arg_node->content, &path_stat) == 0)
        {
            if (S_ISDIR(path_stat.st_mode))
            {
                if (access(arg_node->content, X_OK) == 0) 
                    change_pwd(mbox, arg_node->content);
                else
                    create_error_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": Permission denied");
            }
            else if (S_ISREG(path_stat.st_mode))
                create_error_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": Not a directory");
            else
                create_error_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": No such file or directory");
        }
        else
             create_error_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": No such file or directory");
    }     
}
