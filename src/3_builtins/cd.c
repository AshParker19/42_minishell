/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:31 by astein            #+#    #+#             */
/*   Updated: 2023/12/15 14:16:57 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frankenshell.h"

/**
 * @brief   changes the PWD like
 *          - updates OLDPWD to current PWD
 *          - updates PWD to param 'new_path'
 *          - changes directory via 'chdir'
 * 
 * 			update the exit status to 0
 * 
 * @param   mbox 
 * @param   new_path 
 */
static void	change_pwd(t_mbox *mbox, char *new_path)
{
	char	*temp_pwd;

	if (is_var(mbox, "OLDPWD"))
	{
		temp_pwd = getcwd(NULL, 0);
		set_var_value(mbox, "OLDPWD", temp_pwd);
		free(temp_pwd);
	}
	if (chdir(new_path) != 0)
		err_msg(mbox, EXIT_FAILURE, "nnnn", ERR_P, CD, new_path,
			strerror(errno));
	else
	{
		set_var_value_int(mbox, "?", EXIT_SUCCESS);
		if (is_var(mbox, "PWD"))
		{
			temp_pwd = getcwd(NULL, 0);
			set_var_value(mbox, "PWD", temp_pwd);
			free(temp_pwd);
		}
	}
}

// Check if it's a valid directory
static void	check_dir(t_mbox *mbox, t_ast *arg_node)
{
	struct stat	path_stat;

	if (stat(arg_node->content, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			if (access(arg_node->content, X_OK) == 0)
				change_pwd(mbox, arg_node->content);
			else
				err_msg(mbox, EXIT_FAILURE, "nnnnn", ERR_P, CD,
					arg_node->content, CS, NO_PERM);
		}
		else if (S_ISREG(path_stat.st_mode))
			err_msg(mbox, EXIT_FAILURE, "nnnnn", ERR_P, CD,
				arg_node->content, CS, NO_DIR);
		else
			err_msg(mbox, EXIT_FAILURE, "nnnnn", ERR_P, CD,
				arg_node->content, CS, NO_FOD);
	}
	else
		err_msg(mbox, EXIT_FAILURE, "nnnnn", ERR_P, CD,
			arg_node->content, CS, NO_FOD);
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
 * @param   mbox 
 * @param   arg_node 
 */
void	builtin_cd(t_mbox *mbox, t_ast *arg_node)
{
	if (!arg_node)
	{
		if (is_var(mbox, "HOME"))
			change_pwd(mbox, get_var_value(mbox, "HOME"));
		else
			err_msg(mbox, EXIT_FAILURE, "nn", ERR_P, CD_H);
	}
	else if (arg_node->right)
		err_msg(mbox, EXIT_FAILURE, "nn", ERR_P, CD_A);
	else
		check_dir(mbox, arg_node);
}
