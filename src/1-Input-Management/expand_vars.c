/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/26 20:31:43 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// TODO:the way to check if a variable's name is legal
//          we will need it when we have environment
//   char *var = ft_substr(minibox->input, 0, i);
//         i = 0;
//         while (minibox->input[i])
//         {
//             if (!ft_isalpha(minibox->input[i]))
//             {
//                 ft_putstr_fd(var, 2);
//                 ft_putendl_fd(": command not found", 2);
//                 break ;
//             }
//             i++;
//         }

/* count the amount of dollar sign characters in the string */
// int count_dollars(char *input, int i, int count)
// {
//     int quote_state;

//     quote_state = OUT_Q;

//     while (input[i])
//     {
//         if((*input == IN_SQ || *input == IN_DQ) && quote_state == OUT_Q)
//             quote_state = *input;
//         else if(quote_state ==  *input)
//             quote_state = OUT_Q;

//         printf("cur char %c | cur state %d\n", input[i], quote_state);
//         if(quote_state != IN_DQ && input[i] == '$')
//             count++;
//         i++;
//     }
//     printf("number of $ that are going to be expaned:%d\n",count);
//     return (count);
// }

// /* find the name of the variable to access its value */
// char	*find_key(char *input, int i)
// {
//     input++;
// 	while (ft_isalnum(input[i]) || input[i] == '_')
// 		i++;
// 	return (ft_substr(input, 0, i));	
// }

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
/*
   finds a corresponding whitespace character and returns it
   so the rest part of the input starts with a correct character 
*/
char    find_limiter(char *input, int i)
{
    input++;
    while (ft_isalnum(input[i]) || input[i] == '_')
        i++;
    return (input[i]);    
}

/*
    if a variable was correct thi fucntion
	gets the parts of the string which are located before and after
	the variable name, then expands the variable, and then join all the 3 parts
*/
char    *insert_var_val(char *input, char *var_key, char *var_val, bool found)
{
    char    *first_part;
    char    *rest_part;
    char    *inserted;
    int     first_part_len;
    

    rest_part = ft_strchr(input, '$');
    rest_part = ft_strchr(rest_part, find_limiter(rest_part, 0));
    first_part_len = ft_strlen(input)
		- ft_strlen(rest_part) - (ft_strlen(var_key) + 1); 
    first_part = ft_substr(input, 0, first_part_len);
    if (found == true)
        inserted = ft_strcat_multi(3, first_part, var_val, rest_part);
    else
        inserted = ft_strcat_multi(2, first_part, rest_part);
    free (input);
	free (first_part);
    return (inserted);
}

/*
	traverses through the input string, locates all the variable
	names checking for a dollar sign, stores all the names in
	a string array, then trims spaces at the beginning and the end
	of a string, then replaces all the variable names by their values
*/
// void	expand_variables(t_minibox *minibox, int i, int j)
// {
//     t_bool found_var;
//     minibox->input_expanded = ft_strdup(minibox->input_quoted);
//     minibox->global_vars = get_all_vars(minibox->input_expanded, 0,
//         count_dollars(minibox->input_expanded, 0, 0), NULL);
//     while (minibox->global_vars[++i])
//     {   
//         found_var = ft_false;
//         j = 0;
//         while (minibox->env[j])
//         {
//             int len_var;
//             int len_env_key;
//             char *equal_sign;
//             len_var = ft_strlen(minibox->global_vars[i]);
//             equal_sign = ft_strchr(minibox->env[j], '=');
//             len_env_key = ft_strlen(minibox->env[j]) - ft_strlen(equal_sign);
//             if(len_var == len_env_key)
//             {
//                 if (!ft_strncmp(minibox->global_vars[i], minibox->env[j], len_env_key))
//                 {
//                     found_var = ft_true;
//                     minibox->input_expanded = insert_var_val(minibox->input_expanded,
//                         minibox->global_vars[i], minibox->env[j], true);
//                     break;
//                 }    
//             }
//             j++;    
//         }
//         if(found_var == ft_false)
//         {
//               minibox->input_expanded = insert_var_val(minibox->input_expanded,
//                         minibox->global_vars[i], minibox->env[j], false);
//         }
//     }
// }

// TODO: ALex will code this in the env.c file
char *get_var(char *cur_key)
{
    (void)cur_key;
    char *temp_message = ft_calloc(9, sizeof(char));
    temp_message = "|SOON!|";
    return(temp_message);
}

    // 1. Loop trough qouted_input
    // 2. If we find a $ and are not in qoute_state= single quote
    //  TRUE
    //      3.1.    Find end of var key (so we have the key)
    //      3.2.    Expand var key to value...
    //      3.3.    ... and replace in string
    //          Subcase
    //              only a $
    //              $?
    //  FALSE
    //      4.1.    Remove Quotes but print var key including $
void	expand_variables_2(t_minibox *minibox, int i, int j)
{
    int k;
    int i_end_key;
    int quote_state;
    char *cur_key;
    char *cur_value;
    (void)i;
    (void)j;
    k= 0;
    quote_state = OUT_Q;
    
    minibox->input_expanded = ft_strdup(minibox->input_quoted);
    while(minibox->input_quoted[k])
    {
        // Keeping track off current qoute state
        if((minibox->input_quoted[k] == IN_SQ || minibox->input_quoted[k] == IN_DQ) && quote_state == OUT_Q)
            quote_state = minibox->input_quoted[k];
        else if(quote_state == minibox->input_quoted[k])
            quote_state = OUT_Q;
        if(quote_state != IN_SQ && minibox->input_quoted[k] == '$')
        {
            k++; //skipping the $ sign
            i_end_key = k;
            while (ft_isalnum( minibox->input_quoted[i_end_key]) ||  minibox->input_quoted[i_end_key] == '_')
            {
                i_end_key++;
            }
	        cur_key = ft_substr(minibox->input_quoted, k, i_end_key-k); //TODO:FREE IT
            // TODO: cur_key is "$" or "$?" -> thread special cases
            cur_value = get_var(cur_key); //IF key doesnt exist function returns NULL
            if (cur_value)
                minibox->input_expanded = insert_var_val(minibox->input_expanded, cur_key, cur_value, true);
            else
                minibox->input_expanded = insert_var_val(minibox->input_expanded, cur_key, cur_value, false);
        }            
        k++;
    }
}
