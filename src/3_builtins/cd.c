/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:31 by astein            #+#    #+#             */
/*   Updated: 2023/11/06 15:02:58 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   changes the PWD like
 *          - updates OLDPWD to current PWD
 *          - updates PWD to param 'new_path'
 *          - changes directory via 'chdir'
 * 
 * @param   mbox 
 * @param   new_path 
 */
static void change_pwd(t_mbox *mbox, char *new_path)
{
    set_var_value(mbox, "OLDPWD", ft_strdup(get_var_value(mbox, "PWD")));
    chdir(new_path);
    set_var_value(mbox, "PWD", ft_strdup(getcwd(NULL, 0)));
}


/**
 * @brief   performs multiple tests if the given 'arg_nodes' are correct
 *          if correct the current directory will be changed via 'change_pwd'
 * 
 *          EXAMPLES:
 *        	No args				->	cd to home
 *        	Empty args			->	do nothing
 *          Arg 				->	cd to arg
 *       	Args            	->	too many arguments  
 *        	
 *        
 *          HOME not set		->	cd: HOME not set
 *        	PWD/OLDPWD not set	->	everything works normally when changing
 *                                  but PWD and OLDPWD in ll doesnt update //FIXME:
 * 
 * @param   mbox 
 * @param   arg_node 
 */
void	builtin_cd(t_mbox *mbox, t_ast *arg_node)
{
    struct stat path_stat;

    if (!arg_node)
        change_pwd(mbox, get_var_value(mbox, "HOME"));
    else if (arg_node->right)
        create_err_msg("nn", ERR_PROMT, "cd: too many arguments");
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
                    create_err_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": Permission denied");
            }
            else if (S_ISREG(path_stat.st_mode))
                create_err_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": Not a directory");
            else
                create_err_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": No such file or directory");
        }
        else
             create_err_msg("nnnn", ERR_PROMT, "cd: ", arg_node->content,
                    ": No such file or directory");
    }     
}
