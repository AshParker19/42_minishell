/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:09 by astein            #+#    #+#             */
/*   Updated: 2023/10/14 19:25:30 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool validate_key(char *key)
{
    // check if first char is alpha or _
    // check if all other chars are alphanum including _
    if (!key)
        return (ft_false);
    if (key[0] != '_' && !ft_isalpha(key[0]))
        return (ft_false);
    key++;
    while (*key)
    {
        if (*key != '_' && !ft_isalnum(*key))
            return (ft_false);
        key++;    
    }
    return (ft_true);
}

static void print_error(char *key)
{
    char    *error_msg;

    // 123===========
    
    // if(print_equal)
    //     error_msg = ft_strcat_multi(4, PROMT , ": export: `", key, "=': not a valid identifier");
    // else
    error_msg = ft_strcat_multi(4, PROMT , ": export: `", key, "': not a valid identifier");
    ft_putendl_fd(error_msg, 2);
    free(error_msg);
}

void builtin_export(t_minibox *minibox, t_tree *arg_node)
{
    char    *equal_sign;
    char    *key;
    char    *value;
    
    if(!arg_node)
    {
        // TODO: SORT A TO Z
    }
    while (arg_node)
    {
        equal_sign = NULL;
        equal_sign = ft_strchr(arg_node->content, '=');
        if(!equal_sign)
        {
            if (!validate_key(arg_node->content))
                print_error(arg_node->content);
            // dont do nothing because the = is missing
            // but still print error if needed
        }
        else
        {
            key = ft_substr(arg_node->content, 0,
                ft_strlen(arg_node->content) - ft_strlen(equal_sign));
            value = ft_substr(equal_sign, 1, ft_strlen(equal_sign)-1);
            if (validate_key(key))
                set_var_value(minibox, key, value);
            else
            {
               print_error(arg_node->content);
            }
        }
        arg_node = arg_node->right;
    }
}

