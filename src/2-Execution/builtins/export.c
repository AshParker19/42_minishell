/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:09 by astein            #+#    #+#             */
/*   Updated: 2023/10/21 12:30:17 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if first char is alpha or _
// check if all other chars are alphanum including _
static t_bool validate_key(char *key)
{
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

static char    **bubble_sort(char *env_copy[], int env_count)
{
    int sorted;
    int i;

    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        i = -1;
        while (++i < env_count - 1)
        {
            if (ft_strcmp(env_copy[i], env_copy[i + 1]) > 0)
            {
                ft_swap_strings(&env_copy[i], &env_copy[i + 1]);
                sorted = 0;
            }
        }
        env_count--;
    }
    return (env_copy); 
}

static int  env_counter(t_env_var *env_var)
{
    if (!env_var)
        return (0);
    else
        return (1 + env_counter(env_var->next));
}

static void    sort_and_print_var(t_minibox *minibox)
{
    char    **env_matrix;
    // t_var   *current_var;

    // current_var = minibox->vars;
    
    // env_matrix = ft_calloc(count_vars + 1, sizeof(char *));
    // if (!env_matrix)
    //     return ;
    // while  (++i < count_vars)
    // {
    //     env_matrix[i] = ft_strdup(current_var->key);
    //     current_var = current_var->next;
    // }
    int count_vars;
    count_vars = env_counter(minibox->vars);
    env_matrix = env_to_matrix(minibox);
    env_matrix = bubble_sort(env_matrix, count_vars);
    if (!env_matrix)
        return ;
    int i;
    i = -1;
    while (++i < count_vars)
        printf ("declare -x %s=\"%s\"\n", env_matrix[i],
            get_var_value(minibox, env_matrix[i]));
    free_whatever("m", env_matrix);
}

void builtin_export(t_minibox *minibox, t_tree *arg_node)
{
    char    *equal_sign;
    char    *key;
    char    *value;
    
    if(!arg_node)
        sort_and_print_var(minibox);
    while (arg_node)
    {
        equal_sign = NULL;
        equal_sign = ft_strchr(arg_node->content, '=');
        if(!equal_sign)
        {
            if (!validate_key(arg_node->content))
                create_error_msg("nnnn", ERR_PROMT, "export: `",
                    arg_node->content, "': not a valid identifier");
        }
        else
        {
            key = ft_substr(arg_node->content, 0,
                ft_strlen(arg_node->content) - ft_strlen(equal_sign));
            value = ft_substr(equal_sign, 1, ft_strlen(equal_sign)-1);
            if (validate_key(key))
                set_var_value(minibox, key, value);
            else
                create_error_msg("nnnn", ERR_PROMT, "export: `",
                    arg_node->content, "': not a valid identifier");
        }
        arg_node = arg_node->right;
    }
}

