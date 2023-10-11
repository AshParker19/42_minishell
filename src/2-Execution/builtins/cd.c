/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:31 by astein            #+#    #+#             */
/*   Updated: 2023/10/11 19:00:52 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void change_pwd(t_minibox *minibox, char *new_value)
{
    set_var(minibox, "OLDPWD", get_var(minibox, "PWD"));
    set_var(minibox, "PWD", new_value);
}

static void cd_up(t_minibox *minibox)
{
    // TODO: 
    //maybe use spilt an use all but the last one?
    // if path is root it should saty root
}

// deal with
//  no permission
//  folder doesnt exist

// what happens if path could be absolute or relative??

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
*/
void	builtin_cd(t_minibox *minibox, char *path)
{
    if(!path || ft_strcmp_strict(path, "~"))
        change_pwd(minibox, get_var(minibox, "HOME"));
    else
    {
        if(ft_strcmp_strict(path, "."))
            change_pwd(minibox, get_var(minibox,"PWD"));
        else if(ft_strcmp_strict(path, ".."))
            cd_up(minibox);
    }
        
}