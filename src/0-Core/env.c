/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:31 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/27 15:14:51 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" //TODO:FIXME:Check the bottom of a fileFIXME:TODO:
//TODO: VAR=""hello world"" should be an error TODO:
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


































































































































































// TODO:the way to check if a variable's name is legal
//          we will need it when we have environment
//   char *var = ft_substr(minibox->input, 0, i);
//         i = 0;
//         while (minibox->input[i])
//         {
//             if (!ft_isalpha(minibox->input[i]) || minibox->input[i] == '_')
//             {
//                 ft_putstr_fd(var, 2);
//                 ft_putendl_fd(": command not found", 2);
//                 break ;
//             }
//             i++;
//         }


/*
   this fucntion allocates array of string to hold all the variable's names,
   then it traverses through the input string, looks for dollar sign and creates
   a string with a name of a key to be expanded after
*/
// char    **get_all_vars(char *input, int i, int count, char **vars)
// {
//     int quote_state;

//     quote_state = OUT_Q;
//     //TODO: the case when only dollar sign is inputed!!!
    
//     vars = ft_calloc(count + 1, sizeof(char *));
//     if (!vars)
//         return (NULL);
//      while (*input)
//     {
//         if((*input == IN_SQ || *input == IN_DQ) && quote_state == OUT_Q)
//             quote_state = *input;
//         else if(quote_state ==  *input)
//             quote_state = OUT_Q;

//         printf("cur char %c | cur state %d\n", input[0], quote_state);
//         if(quote_state != IN_SQ && input[i] == '$')
//         {
//             vars[i] = find_key(ft_strchr(input, '$'), 0);
//             input += ft_strlen(vars[i]);
//             i++;
//         }
//         else
//             input++;
//     }   
//     return (vars);
// }