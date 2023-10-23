/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/10/23 22:37:04 by anshovah         ###   ########.fr       */
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

static void append_chr(t_minibox *minibox, char add_chr)
{
    char    *temp;

    temp =  ft_strcat_multi(2, minibox->input_expanded, ft_chr2str(add_chr));
    free(minibox->input_expanded);
    minibox->input_expanded = temp;
    printf("current expansion (%s)\n", temp);
}

static void append_str(t_minibox *minibox, char *add_str)
{
    char    *temp;

    temp =  ft_strcat_multi(2, minibox->input_expanded, add_str);
    free(minibox->input_expanded);
    minibox->input_expanded = temp;
    printf("current expansion (%s)\n", temp);
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
    int     old_qoute_state;
    int     end_of_key;
    char    *temp_key;
    
    temp_key =NULL;
    minibox->input_expanded = NULL;
    while (minibox->input_quoted[k])
    {
        cur_char = minibox->input_quoted[k];
        update_qoute_state(&quote_state, cur_char);
        if (quote_state != add_offset('\'') && cur_char == '$')
        {
            // we found a $
            old_qoute_state = quote_state;
            k++;
            cur_char = minibox->input_quoted[k];
            printf("cur char (%c)\n", cur_char);
            if (cur_char != '\0')
            {
                update_qoute_state(&quote_state, cur_char);
                if (quote_state != old_qoute_state)
                {
                    // found a qoute so ignore the $ but copy the '
                    // e.g. echo $'LOL' -> echo LOL
                    append_chr(minibox, cur_char);
                }
                else if(cur_char == '?')
                    append_str(minibox, ft_itoa(minibox->executor.exit_status));
                else if (cur_char == NO_SPACE || cur_char == ' ')
                {
                    append_chr(minibox, '$');
                    append_chr(minibox, ' ');
                }
                // 1. check if first char of keyalphanum or _
                else if (ft_isalnum(cur_char) || cur_char == '_')
                {
                    // find end of key
                    end_of_key = k;
                    // while strin isnt over and alphanum or _ we have a key
                    while(minibox->input_quoted[end_of_key] && (ft_isalnum(minibox->input_quoted[end_of_key]) || minibox->input_quoted[end_of_key] == '_'))
                    {
                        end_of_key++;
                    }
                    temp_key = ft_substr(minibox->input_quoted, k, end_of_key -k );
                    append_str(minibox, get_var_value(minibox, temp_key));
                    free(temp_key);
                    k = end_of_key -1 ;
                }
                    
                else
                {
                    printf("AFTER THE $ ther is no valid beginning of an key so skip it\n");   
                    printf("The only exuse are no contextual qoutes! we need to print them anyway\n");   
                    if(cur_char == '\'' || cur_char == '"')
                    {
                        append_chr(minibox, '$');
                        append_chr(minibox, cur_char);
                    }
                }
                    ;
                // if yes - valid key
 
                // else
                // ignore one char and continue
            }
            else
            {
                // string is over becaus we reached the end of the inpu
                // so just copy the fucking $
                // example "echo hi $"
                append_chr(minibox, '$');
            }
        }
        else
        {
            // just fucking  copy
           append_chr(minibox, cur_char);
        }
        k++;
    }
}



// // if (minibox->input_quoted[k] == '?')
//             //    minibox->input_expanded =
//             //     insert_exit_status(minibox->input_expanded, &minibox->input_quoted[k], minibox->executor.exit_status);
//             // else
//             // {
//                 k_end = k;
//                 while ((ft_isalnum(minibox->input_quoted[k_end])
//                     ||  minibox->input_quoted[k_end] == '_'))
//                     k_end++;
//                 cur_key = ft_substr(minibox->input_quoted, k, k_end - k);
//                 cur_value = get_var_value(minibox, cur_key); //TODO: try to sent an address of a current index
//                 minibox->input_expanded = insert_value(minibox->input_expanded, cur_key, cur_value, OUT_Q);
//                 free(cur_key);     
//             // }