/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:09 by astein            #+#    #+#             */
/*   Updated: 2023/10/29 01:29:24 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// check if first char is alpha or _
// check if all other chars are alphanum including _
/**
 * @brief   checks if the 'key' is valid
 *          - can't be NULL
 *          - the first char has to be alpha or '_'
 *          - the rest has to alphanum or '_'
 * 
 * @param   key 
 * @return  t_bool 
 */
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

/**
 * @brief   uses simple bubble sort method to sort 'env_copy' alphabetically
 * 
 * @param   env_copy 
 * @param   env_count 
 * @return  char** 
 */
static char    **bubble_sort(char **env_copy, int env_count)
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

/**
 * @brief   recursively traverses through the ll and return
 *          the amount of nodes in it
 * 
 * @param   env_var 
 * @return  int     amount of nodes
 */
static int  env_counter(t_env_var *env_var)
{
    if (!env_var)
        return (0);
    else
        return (1 + env_counter(env_var->next));
}

/**
 * @brief   uses 'env_counter' to determine the size of the 't_env_var' ll;
 *          creates a matrix of the ll via 'env_to_matrix' and passes those
 *          informations to 'bubble_sort' to sort the array.
 * 
 *          prints the sorted matris to STDOUT //FIXME: PIPE CMD INSTEAD
 * 
 *          NOTE: the -1 for count_vars is becaus of the '?' node in the ll
 * 
 * @param   mbox 
 */
static void    sort_and_print_var(t_mbox *mbox)
{
    char    **env_matrix;
    int count_vars;
    
    count_vars = env_counter(mbox->env_vars) - 1;
    env_matrix = env_to_matrix(mbox);
    env_matrix = bubble_sort(env_matrix, count_vars);
    if (!env_matrix)
        return ;
    int i;
    i = -1;
    while (++i < count_vars)
        printf ("declare -x %s=\"%s\"\n", env_matrix[i],
            get_var_value(mbox, env_matrix[i]));
    free_whatever("m", env_matrix);
}

/**
 * @brief   responsible for 2 things:
 *              if doesnt have one 'arg_node'
 *                  sorts & prints the 't_env_var' ll via 'sort_and_print_var'
 *              else
 *                for each 'arg_node'
 *                  CASE: correct (PATH=hello)
 *                          ->add/changes value in ll
 *                  CASE: no equal sign & correct key (PATH)
 *                          ->ignores the arg / dont do nothing
 *                  CASE: equal sign & wrong key (@=lol)
 *                          -> export: `@=LL': not a valid identifier
 *                  CASE: no equal sign & wrong key (@)
 *                          -> export: `@': not a valid identifier
 * @param   mbox 
 * @param   arg_node 
 */
void builtin_export(t_mbox *mbox, t_ast *arg_node)
{
    char    *equal_sign;
    char    *key;
    char    *value;
    
    if (!arg_node)
        sort_and_print_var(mbox);
    while (arg_node)
    {
        equal_sign = NULL;
        equal_sign = ft_strchr(arg_node->content, '=');
        if (!equal_sign)
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
                set_var_value(mbox, key, value);
            else
                create_error_msg("nnnn", ERR_PROMT, "export: `",
                    arg_node->content, "': not a valid identifier");
        }
        arg_node = arg_node->right;
    }
}
