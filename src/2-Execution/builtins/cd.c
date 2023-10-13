/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:31 by astein            #+#    #+#             */
/*   Updated: 2023/10/14 00:10:50 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cd_up(t_minibox *minibox)
{
    char    *path;
    char    *old_pwd;

    old_pwd = get_var(minibox, "PWD");
    path = ft_strrchr(old_pwd, '/');
    path = ft_substr(old_pwd, 0, ft_strlen(old_pwd) - ft_strlen(path));
    free(old_pwd);
    set_var(minibox, "PWD", path);
}

/*
    The path is valid so splid and go there!
    path can't be NULL
*/
static void cd_to_path(t_minibox *minibox, char *new_path)
{
    char    **folders;
    char    *old_pwd;
    int     i;
    char    *temp;
    
    // /usr/bin/./././../bin/lol
    // src/../../../././../Documents/../Downloads
    printf("HIII\n");
    folders = ft_split(new_path, '/');
    old_pwd = get_var(minibox, "PWD");
    if(new_path[0] == '/')
        set_var(minibox, "PWD", "/");
    i = 0;
    while(folders[i])
    {
        if (ft_strcmp_strict(folders[i], ".."))
            cd_up(minibox);
        else if (ft_strcmp_strict(folders[i], "."))
            ;
        else
        {
            temp = ft_strcat_multi(3, get_var(minibox, "PWD"), folders[i], "/");
            set_var(minibox, "PWD", temp);
            free(temp);
        }
        i++;
    }
    free_matrix(folders, -1);
}

static void change_pwd(t_minibox *minibox, char *new_path)
{
    free(get_var(minibox, "OLDPWD"));
    set_var(minibox, "OLDPWD", get_var(minibox, "PWD"));
    set_var(minibox, "PWD", ft_strdup(new_path));
    // chdir(get_var(minibox, "PWD"));
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

    doenst matter if it ends on / or not
    cd Documents/../../astein/Downloads/../../../../../../
    cd Documents/../../astein/Downloads/../../../../../..

*/
void	builtin_cd(t_minibox *minibox, t_tree *arg_node)
{
    char *error_str;
    char *path;

    if (!arg_node)
    {
        printf("home %s\n", get_var(minibox, "HOME"));
        change_pwd(minibox, get_var(minibox, "HOME"));
    }
    else if (arg_node->right)
    {
        ft_putstr_fd(PROMT, 1);
        ft_putendl_fd (" cd: too many arguments", 1);
    }
    else
    {
        path = arg_node->content;
        if (access(path, F_OK) == -1)
        {
            error_str = ft_strcat_multi(4, PROMT, "cd: ", path, ": No such file or directory");
            ft_putendl_fd (error_str, 1);
            free(error_str);
        }
        else
            cd_to_path(minibox, path);
    }
        
    // if(ft_strcmp_strict(path, "./"))
    //     //relative path (maybe ././././../ in there
    //     ;
    // else if(ft_strcmp_strict(path, "."))
    //         change_pwd(minibox, get_var(minibox,"PWD"));
    // else if(ft_strcmp_strict(path, "/"))
    //     // absolute path
    //     ;
    // else if(ft_strcmp_strict(path, "~"))
        
    // else if(ft_strcmp_strict(path, ".."))
    //     cd_up(minibox);
    
   
}