/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/26 19:49:20 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    input a key and function reuturns expanded value for all env and local vars

                ENV         LOCAL
    --------|----------------------
    input   |   LESS        ALEX
    return  |   -R          ANATOLII
*/
char *get_var(char *key)
{
    
}

void set_var(t_minibox *minibox, char *key, char *value)
{
    // called from
    // PATH=123             (change env)
    // ALEX=ANATOLII        (change local)
    // export HELLO=WORLD   (create env var)
    // checks if env or local and changes or creates it


    /*
        FIXME: IDEA

        save env and local vars in to sperate files
            - create a local file and
            - env > current_env.env
        use the same function to chek if a key is in there
        save all vars there
        fuck the linked list!

        on exit minishell
            - restore original env (if nessesary -> dont know yet)
            - delete the two files
    
    */
}

// REPLACING $LESS ---> -R
//    1 check if Var KEY is a GLOBAL one
//    2 check if local one
//    3 if not 1 ord 2 delete it (HELLO $LES WOLRD   -> Hello  World)
// Input a VAR Key
// Returns Value (NULL if doenst exist)
// 
// Input $ANATOLII
// Return ALEX
char *get_local_var(char *key)
{
    (void)key;
    return(NULL);
}

// SET VARS    LESS=ASD
//      1 Check i KEY is a GLOBAL one -> overwrite global one
//      2 Check if already a local one -> overwrite local one
//      3 If not 1 or 2 than declare a new local one (add to linked list)
void set_local_var(t_minibox *minibox, char *key, char *value)
{
    int i;

    while(minibox->env[i])
    {
        if()
    }
    (void)minibox;    
    (void)key;
    (void)value;    
    // TODO:
}

// DELETE AND FREE THE LINKED LIST
void free_local_vars(t_minibox *minibox)
{
    (void)minibox;
    // TODO:
}

