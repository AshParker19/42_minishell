/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/23 14:59:01 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
    used to find the end of an var key.
    a key ends if the next char is not alphanum or underscore
    returns: the character which is located after a "word"
*/
char    find_limiter(char *input, int i)
{
    input++;
    while (ft_isalnum(input[i]) || input[i] == '_')
        i++;
    return (input[i]);    
}

/*
    if a variable key was correct this fucntion gets the parts of the string 
    which are located before and after the variable name, then expands 
    the variable, and then join all the 3 parts, if a key wasn't correct, 
    it joins what was before and after the variable
*/
char    *insert_value(char *input, char *key, char *value, int quote_state)
{
    char    *first_part;
    char    *rest_part;
    int     first_part_len;
    char    *inserted;

    rest_part = input;
    while (*rest_part)
    {
        update_qoute_state(&quote_state, *rest_part);
        if (quote_state != add_offset('\'') && *rest_part == '$')
            break;
        rest_part++;
    }
    rest_part = ft_strchr(rest_part, find_limiter(rest_part, 0));
    first_part_len = ft_strlen(input)
		- ft_strlen(rest_part) - (ft_strlen(key) + 1); 
    first_part = ft_substr(input, 0, first_part_len);
    if (value)
        inserted = ft_strcat_multi(3, first_part, value, rest_part);
    else
        inserted = ft_strcat_multi(2, first_part, rest_part);
    free (input);
	free (first_part);
    return (inserted);
}

// char    *insert_exit_status(char *input, char *question_mark, int exit_status)
// {
//     char    *rest_part;
//     char    *first_part;
//     int     first_part_len;
    
//     rest_part = ft_strchr(question_mark, '?');
//     printf ("REST 1 %s\n", rest_part);
//     rest_part++;
//     printf ("REST 2 %s\n", rest_part);
//     printf ("LEN111 %zu\n", ft_strlen(rest_part));
    
//     printf ("INPUTA %s\n", first_part);
//     return (NULL);
// }

/*
	traverses through the input string, locates all the variable
	names checking for a dollar sign, then replaces all the variable names
    by their values which are received from environment
*/
void	expand_variables(t_minibox *minibox, int k, int k_end, int quote_state)
{
    char    *cur_key;
    char    *cur_value;
    char    cur_char;
    
    minibox->input_expanded = ft_strdup(minibox->input_quoted);
    while (minibox->input_quoted[k])
    {
        cur_char = minibox->input_quoted[k];
        update_qoute_state(&quote_state, cur_char);
        if (quote_state != add_offset('\'') && cur_char == '$')
        {
            k++;
            // if (minibox->input_quoted[k] == '?')
            //    minibox->input_expanded =
            //     insert_exit_status(minibox->input_expanded, &minibox->input_quoted[k], minibox->executor.exit_status);
            // else
            // {
                k_end = k;
                while ((ft_isalnum(minibox->input_quoted[k_end])
                    ||  minibox->input_quoted[k_end] == '_'))
                    k_end++;
                cur_key = ft_substr(minibox->input_quoted, k, k_end - k);
                cur_value = get_var_value(minibox, cur_key); //TODO: try to sent an address of a current index
                minibox->input_expanded = insert_value(minibox->input_expanded, cur_key, cur_value, OUT_Q);
                free(cur_key);     
            // }
        }            
        k++;
    }
}
