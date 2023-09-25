/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/25 18:34:47 by anshovah         ###   ########.fr       */
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
	while (ft_isalnum(input[i]) || input[i] == '_')
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
	gets the parts of the string which are located before and after
	the variable name, then expands the variable, and then join all the 3 parts
*/
char    *insert_var_val(char *input, char *var_name, char *var_value)
{
    char    *first_part;
    char    *rest_part;
    char    *inserted;
    int     first_part_len;
    
    rest_part = ft_strchr(input, '$');
    rest_part = ft_strchr(rest_part, ' ');
    first_part_len = ft_strlen(input)
		- ft_strlen(rest_part) - (ft_strlen(var_name) + 1); 
    first_part = ft_substr(input, 0, first_part_len);
    var_value += (ft_strlen(var_name) + 1);
    inserted = ft_strcat_multi(3, first_part, var_value, rest_part);
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
void	expand_variables(t_minibox *minibox, int i, int j)
{
    t_bool flg_found_var;
    minibox->input_expanded = ft_strdup(minibox->input_trimmed);
    minibox->vars = get_all_vars(minibox->input_expanded, 0,
        count_dollars(minibox->input_expanded, 0, 0), NULL);
    while (minibox->vars[++i])
    {   
        flg_found_var = ft_false;
        j = 0;
        while (minibox->env[j])
        {
            int len_var;
            int len_env_key;
            char *equal_sign;
            len_var = ft_strlen(minibox->vars[i]);
            equal_sign = ft_strchr(minibox->env[j], '=');
            len_env_key = ft_strlen(minibox->env[j]) - ft_strlen(equal_sign);
            if(len_var == len_env_key)
            {
                if (!ft_strncmp(minibox->vars[i], minibox->env[j], len_env_key))
                {
                    flg_found_var = ft_true;
                    minibox->input_expanded = insert_var_val(minibox->input_expanded,
                    minibox->vars[i], minibox->env[j]);
                    break;
                }    
            }
            j++;    
        }
        if(flg_found_var == ft_false)
        {
            // TODO: We have to remove the wrong var in the string like:
            // Hello $LES World    ->   Hello  World 
        }
    }
}
