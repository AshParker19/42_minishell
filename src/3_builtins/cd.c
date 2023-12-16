/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:31 by astein            #+#    #+#             */
/*   Updated: 2023/12/16 01:45:33 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief   This file contains the builtin 'cd' function, which changes the
 * 			current working directory.
 *  		This includes:
 * 				- argument(s) checking (no args, too many args, empty arg)
 * 				- argument string checking (directory, file, permission)
 * 				- directory changing (via 'chdir')
 * 				- environment variable checking (HOME, OLDPWD, PWD)
 * 				- enviroment variable updating (OLDPWD, PWD)
 * 				- exit status updating
 * 
 * 			DOCUMENTATION:
 * 			https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#cd 			
 */

#include "frankenshell.h"

/**
 * @brief   This function then finally:
 * 				- changes the current working directory via 'chdir'
 * 				- updates the variables 'OLDPWD' and 'PWD' if they exist
 * 				- sets the exit status to 0
 * 
 * 			If 'chdir' fails, an error message will be printed (exit status = 1)
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
		if (is_var(mbox, "PWD"))
		{
			temp_pwd = getcwd(NULL, 0);
			set_var_value(mbox, "PWD", temp_pwd);
			free(temp_pwd);
		}
		set_var_value_int(mbox, "?", EXIT_SUCCESS);
	}
}

/**
 * @brief   This function checks if the given 'new_path' is
 *	
 * 	-> a directory	-> with permission		-> change directory via 'change_pwd'
 * 					-> without permission	-> error: 'cd: Permission denied'
 * 	-> a file		-> error: 'cd: Not a directory'
 * 
 * 			DOCUMENTATION:
 * 			https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#cd
 * 			
 * @param   mbox        
 * @param   new_path    
 */
static void	check_dir(t_mbox *mbox, char *new_path)
{
	struct stat	path_stat;

	if (stat(new_path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			if (access(new_path, X_OK) == 0)
				change_pwd(mbox, new_path);
			else
				err_msg(mbox, EXIT_FAILURE, "nnnnn", ERR_P, CD,
					new_path, CS, NO_PERM);
		}
		else if (S_ISREG(path_stat.st_mode))
			err_msg(mbox, EXIT_FAILURE, "nnnnn", ERR_P, CD,
				new_path, CS, NO_DIR);
		else
			err_msg(mbox, EXIT_FAILURE, "nnnnn", ERR_P, CD,
				new_path, CS, NO_FOD);
	}
	else
		err_msg(mbox, EXIT_FAILURE, "nnnnn", ERR_P, CD,
			new_path, CS, NO_FOD);
}

/**
 * @brief   This Builtin changes the current working directory.
 * 			It performs multiple tests if the given 'arg_node' is correct
 *          if correct the current directory will be changed via 'change_pwd'
 * 
 *          EXAMPLES:
 *        	no args			-> if HOME is set		-> cd to home
 * 							-> else					-> error: 'cd: HOME not set'
 *       	multiple args   -> error 'cd: too many arguments'
 *        	empty args		-> do nothing (exit status = 0)
 *          arg 			-> cd to arg via 'check_dir'
 *        	
 * 			DOCUMENTATION:
 * 			https://github.com/ahokcool/frankenshell/blob/main/docs/documentation.md#cd 			
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
	else if (arg_node->content && arg_node->content[0] == '\0')
		set_var_value_int(mbox, "?", EXIT_SUCCESS);
	else
		check_dir(mbox, arg_node->content);
}
