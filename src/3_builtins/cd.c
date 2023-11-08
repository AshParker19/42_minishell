/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:31 by astein            #+#    #+#             */
/*   Updated: 2023/11/08 00:04:27 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   changes the PWD like
 *          - updates OLDPWD to current PWD
 *          - updates PWD to param 'new_path'
 *          - changes directory via 'chdir'
 * 
 *          NOTE:
 *          If HOME is not set (e.g. via 'unset HOME') the PWD and OLDPWD are
 *          not supposed to update!
 * 
 * @param   mbox 
 * @param   new_path 
 */
static void change_pwd(t_mbox *mbox, char *new_path)
{
    static  int first_pwd_unset;
    
    if (is_var(mbox, "OLDPWD"))
        set_var_value(mbox, "OLDPWD", ft_strdup(getcwd(NULL, 0)));
    // else
    // {
    //     if (first_pwd_unset == 0)
    //     {
    //         delete_var(mbox, "OLDPWD");
    //         first_pwd_unset = 1;
    //     }
    //     else
    //         set_var_value(mbox, "OLDPWD", ft_strdup(getcwd(NULL, 0)));        
    // }
    chdir(new_path);
    if (is_var(mbox, "PWD"))
        set_var_value(mbox, "PWD", ft_strdup(getcwd(NULL, 0)));
}


/**
 * @brief   performs multiple tests if the given 'arg_nodes' are correct
 *          if correct the current directory will be changed via 'change_pwd'
 * 
 *          EXAMPLES:
 *        	no args				->	cd to home
 *        	empty args			->	do nothing
 *          arg 				->	cd to arg
 *       	args            	->	too many arguments  
 *        	
 *          CASE:
 *          HOME NOT SET (e.g. via 'unset HOME')
 *              -> no args      ->	cd: HOME not set
 * 
 *          TODO:
 *          "The return status is zero if the directory is successfully changed, non-zero otherwise."
 * 
 * @param   mbox 
 * @param   arg_node 
 */
void	builtin_cd(t_mbox *mbox, t_ast *arg_node)
{
    struct stat path_stat;

    if (!arg_node)
    {
        if (is_var(mbox, "HOME"))
            change_pwd(mbox, get_var_value(mbox, "HOME"));
        else
            put_err_msg("nn", ERR_PROMT, "cd: HOME not set");
    }
    else if (arg_node->right)
        put_err_msg("nn", ERR_PROMT, "cd: too many arguments");
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
                    put_err_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": Permission denied");
            }
            else if (S_ISREG(path_stat.st_mode))
                put_err_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": Not a directory");
            else
                put_err_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": No such file or directory");
        }
        else
             put_err_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": No such file or directory");
    }     
}
