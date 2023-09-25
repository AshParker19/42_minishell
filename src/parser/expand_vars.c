/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/25 12:08:16 by anshovah         ###   ########.fr       */
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
int count_dollars(char *input, int i, int count)
{
    while (input[i])
    {
        if (input[i] == '$')
            count++;
        i++;
    }
    return (count);
}

/* find the name of the variable to access its value */
char	*find_key(char *input, int i)
{
    input++;
	while (ft_isalnum(input[i]))
		i++;
	return (ft_substr(input, 0, i));	
}

/*
   this fucntion allocates array of string to hold all the variable's names,
   then it traverses through the input string, looks for dollar sign and creates
   a string with a name of a key to be expanded after
*/
char    **get_all_vars(char *input, int i, int count, char **vars)
{
    //TODO: the case when only dollar sign is inputed!!!
    
    vars = ft_calloc(count + 1, sizeof(char *));
    if (!vars)
        return (NULL);
     while (*input)
    {
        if (*input == '$')
        {
            vars[i] = find_key(ft_strchr(input, '$'), 0);
            input += ft_strlen(vars[i]);
            i++;
        }
        else
            input++;
    }   
    return (vars);
}

/*
   trims all the whitespaces at the beginning and the end 
   of the original string, frees it and returns the trimmed one
*/
char    *trim_input(char *input)
{
    char    *trimmed;

    trimmed = ft_strtrim(input, " \n\t\v");
    if (input)
        free (input);        
    return (trimmed);
}
/* looknig for the index of a dollar sign character in the string */
int find_dollar(char *input, int i)
{
    while (input[i])
    {
        if (input[i] == '$')
            break ;
        i++;
    }
    return (i);
}

char    *str_copy3(char *s1, char *s2, char *s3, int s1_len)
{
    int     i;
    int     s2_len;
    int     s3_len;
    char    *copied;

    i = 0;
    s2_len = ft_strlen(s2);
    s3_len = ft_strlen(s3);
    copied = ft_calloc(s1_len + s2_len + s3_len + 1, sizeof(char));
    if (!copied)
        return (NULL);
    while (i < s1_len)
    {
        copied[i] = s1[i];
        i++;
    }
    while (i < s2_len)
    {
        copied[i] = s2[i];
        i++;
    }
    while (i < s3_len)
    {
        copied[i] = s3[i];
        i++;
    }
    return (copied);
}

char    *insert_var_val(char *input, char *var_name, char *var_value)
{
    int     rest_len;
    int     input_len;
    int     name_len;
    char    *first_part;
    char    *rest_part;
    int     first_part_len;
    char    *inserted;
    size_t  lcpy;
    
    rest_part = ft_strchr(input, '$');
    rest_part = ft_strchr(rest_part, ' ');
    input_len = ft_strlen(input);
    name_len = ft_strlen(var_name) + 1;
    rest_len = ft_strlen(rest_part);
    // len of the string - len of the rest - len name of var - 1(for '=' sign)
    first_part_len = input_len - rest_len - name_len - 1; 
    first_part = ft_substr(input, 0, first_part_len);
    var_value += name_len;
    inserted = ft_calloc(first_part_len + ft_strlen(var_value) + rest_len + 1, sizeof(char));
    if (!inserted)
        return (NULL);
        
    //TODO: don't forget to free the original string and what was returned by substr
    return (NULL);
}

char	*expand_variables(t_minibox *minibox, int i, int j)
{
    minibox->vars = get_all_vars(minibox->input, 0,
        count_dollars(minibox->input, 0, 0), NULL);
    minibox->input = trim_input(minibox->input);
    while (minibox->vars[i])
    {   
        j = 0;
        while (minibox->env[j])
        {
            if (!ft_strncmp(minibox->vars[i], minibox->env[j],
                ft_strlen(minibox->vars[i])))
            {
                minibox->input = insert_var_val(minibox->input,
                minibox->vars[i], minibox->env[j]);
            }    
            j++;    
        }
        i++;
    }
    // while (minibox->vars[i])
    // {
    //     minibox->input = double_join(minibox, minibox->input,
    //         minibox->vars[i], 0);
    //     i++;    
    // }
	return (NULL);
}
