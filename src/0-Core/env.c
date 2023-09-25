/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/25 19:46:50 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// REPLACING $LESS ---> -R
//    1 check if Var KEY is a GLOBAL one
//    2 check if local one
//    3 if not 1 ord 2 delete it (HELLO $LES WOLRD   -> Hello  World)
// Input a VAR Key
// Returns Value (NULL if doenst exist)
// 
// Input $ANATOLII
// Return ALEX
char *resolve_local_var(char *key)
{
    (void)key;
    return(NULL);
}

// SET VARS    LESS=ASD
//      1 Check i KEY is a GLOBAL one -> overwrite global one
//      2 Check if already a local one -> overwrite local one
//      3 If not 1 or 2 than declare a new local one (add to linked list)
void store_local_var(t_minibox *minibox, char *key, char *value)
{
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

