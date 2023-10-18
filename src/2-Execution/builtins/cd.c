/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:32:31 by astein            #+#    #+#             */
/*   Updated: 2023/10/18 16:33:02 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void print_error(char *path)
{
    char    *error_msg;
    
    error_msg = ft_strcat_multi(4, PROMT, ": cd: ", path, ": No such file or directory");    
    ft_putendl_fd(error_msg, 2);
    free(error_msg);
}

// static void cd_up(t_minibox *minibox, char **temp_path)
// {
//     char    **folders;
//     char    *buffer;
//     int     i;
    
//     buffer = NULL;
//     if(temp_path && *temp_path)
//         if (ft_strcmp_strict(*temp_path, "/"))
//             return ;
    
//     folders = ft_split(*temp_path, '/');
//     i = 0;
//     free(*temp_path);
//     *temp_path = ft_strdup("/");
//     if(!folders)
//     {
//         while(*folders[i])
//         {
//             if(*folders[i+1])
//             {
//                 buffer = ft_strcat_multi(3, *temp_path, "/", *folders[i]);
//                 free(*temp_path);
//                 *temp_path = buffer;
//             }
//             i++;
//         }
//     }
// }

/*
    The path is valid so split and go there!
    path can't be NULL
*/
// static void cd_to_path(t_minibox *minibox, char *target_path, char **temp_path)
// {
    // char    **folders;
    // int     i;
    // char    *buffer;
    
    // folders = ft_split(target_path, '/');
    // if(target_path[0] == '/')
    // {
    //     printf("ABSOLUTE PATH!\n");
    //     *temp_path = "/";
    // }
    // else
    //     printf("RELATIVE PATH!\n");
    // i = 0;
    // printf("CUR\t%s\nTARGET\t%s\n", *temp_path, target_path);
    // while(folders[i])
    // {
    //     if (ft_strcmp_strict(folders[i], ".."))
    //         cd_up(minibox, temp_path);
    //     else if (ft_strcmp_strict(folders[i], "."))
    //         ;
    //     else
    //     {
    //         if (ft_strcmp_strict(*temp_path, "/"))
    //         {
    //             buffer = *temp_path;
    //             *temp_path = ft_strcat_multi(2, *temp_path, folders[i]);
    //             // free(buffer);
    //         }
    //         else
    //         {
    //             buffer = *temp_path;
    //             *temp_path = ft_strcat_multi(3, *temp_path, "/", folders[i]);
    //             free(buffer);
    //         }
    //         printf("new path (%s)\n", *temp_path);
    //     }
    //     i++;
    // }
    // free_whatever("m", folders);
// }

static void change_pwd(t_minibox *minibox, char *new_path)
{
    set_var_value(minibox, "OLDPWD", ft_strdup(get_var_value(minibox, "PWD")));
    chdir(get_var_value(minibox, "PWD"));
    set_var_value(minibox, "PWD", ft_strdup(getcwd(NULL, 0)));
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
    char *target_path;
    char *temp_path;

    temp_path = NULL;

    if (!arg_node)
        temp_path = get_var_value(minibox, "HOME");
    else if (arg_node->right)
    {
        ft_putstr_fd(PROMT, STDERR_FILENO);
        ft_putendl_fd (": cd: too many arguments", STDERR_FILENO);
    }
    else
    {
        // target_path = arg_node->content;
        // if (target_path[0] == '~')
        // {
        //     if (target_path[1] == '/')
        //     {
        //         temp_path = get_var_value(minibox, "HOME");
        //         target_path +=2;
        //     }
        //     else
        //     {
        //         print_error(target_path);
        //         return ;
        //     }       
        // }
        if (access(target_path, F_OK) == -1)
            print_error(target_path);
        else
            change_pwd(minibox, target_path);   
    }

    if(temp_path)
        change_pwd(minibox, temp_path);
}