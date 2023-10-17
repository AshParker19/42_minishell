/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:09 by astein            #+#    #+#             */
/*   Updated: 2023/10/17 15:20:36 by anshovah         ###   ########.fr       */
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

    error_msg = ft_strcat_multi(4, PROMT , ": export: `", key, "': not a valid identifier");
    ft_putendl_fd(error_msg, 2);
    free(error_msg);
}

static int  env_counter(t_var *env_var)
{
    if (!env_var)
        return (0);
    else
        return (1 + env_counter(env_var->next));
}

char    **bubble_sort(char *env_copy[], int env_count)
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

static void    sort_and_print_var(t_var *env_var, int env_count, int i)
{
    char    **env_copy;
    
    env_copy = ft_calloc(env_count + 1, sizeof(char *));
    if (!env_copy)
        return ;
    while  (++i < env_count)
    {
        env_copy[i] = ft_strdup(env_var->key);
        env_var = env_var->next;
    }
    env_copy = bubble_sort(env_copy, env_count);
    if (!env_copy)
        return ;
    i = -1;
    while (++i < env_count)
        printf ("declare -x %s=\"%s\"\n", env_copy[i], getenv(env_copy[i]));
    //FIXME: for some reason prints one more variable whose name is '_' at the end
    free_whatever("m", env_copy);
}

void builtin_export(t_minibox *minibox, t_tree *arg_node)
{
    char    *equal_sign;
    char    *key;
    char    *value;
    
    if(!arg_node)
        sort_and_print_var(minibox->vars, env_counter(minibox->vars), -1);
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

