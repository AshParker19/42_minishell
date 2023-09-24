/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:58:49 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/24 22:11:54 by anshovah         ###   ########.fr       */
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

char    *trim_and_join(char *input)
{
    char    *trimmed;

    trimmed = ft_strtrim(input, " \n\t\v");
    if (input)
        free (input);        
    return (NULL);
}

char	*expand_variables(t_minibox *minibox, int i, int j)
{
    minibox->vars = get_all_vars(minibox->input, 0,
        count_dollars(minibox->input, 0, 0), NULL);
    i = 0, j = 0;
    minibox->input = trim_and_join(minibox->input);
    // while (minibox->vars[i])
    // {   
    //     j = 0;
    //     while (minibox->env[j])
    //     {
    //         if (!ft_strncmp(minibox->vars[i], minibox->env[j],
    //             ft_strlen(minibox->vars[i])))
    //             printf ("%s\n", minibox->env[j]);
    //         j++;    
    //     }
    //     i++;
    // }
	return (NULL);
}
