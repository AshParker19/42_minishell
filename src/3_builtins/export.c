/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:09 by astein            #+#    #+#             */
/*   Updated: 2023/11/22 09:54:26 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * @brief   recursively traverses through the ll and return
 *          the amount of nodes in it
 * 
 * @param   env_var 
 * @return  int     amount of nodes
 */
static int  env_counter(t_env *env_var)
{
    if (!env_var)
        return (0);
    else
        return (1 + env_counter(env_var->next));
}

/**
 * @brief   uses simple bubble sort method to sort 'env_copy' alphabetically
 * 
 * @param   env_copy 
 * @param   env_count 
 * @return  char** 
 */
static char    **bubble_sort(const t_mbox *mbox, char **env_matrix)
{
    int sorted;
    int i;
	int env_count;

	env_count = env_counter(mbox->env) - 1;
    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        i = -1;
        while (++i < env_count - 1)
        {
            if (ft_strcmp(env_matrix[i], env_matrix[i + 1]) > 0)
            {
                ft_swap_strings(&env_matrix[i], &env_matrix[i + 1]);
                sorted = 0;
            }
        }
        env_count--;
    }
    return (env_matrix); 
}

/**
 * @brief   uses 'env_counter' to determine the size of the 't_env' ll;
 *          creates a matrix of the ll via 'env_to_matrix' and passes those
 *          informations to 'bubble_sort' to sort the array.
 * 
 * @param   mbox 
 */
static void    sort_and_print_var(const t_mbox *mbox)
{
    char    **env_matrix;
    int		i;
    
    env_matrix = env_to_matrix(mbox, "\"");
    env_matrix = bubble_sort(mbox, env_matrix);
    if (!env_matrix)
        return ;
    i = -1;
    while (env_matrix[++i])
	{
		ft_putstr_fd("declare -x ", mbox->executor.io.cmd_fd[CMD_OUT]);
		ft_putendl_fd(env_matrix[i], mbox->executor.io.cmd_fd[CMD_OUT]);
	}
    free_whatever("m", env_matrix);
}

/**
 * @brief   responsible for 2 things:
 *              if doesnt have one 'arg_node'
 *                  sorts & prints the 't_env' ll via 'sort_and_print_var'
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
	t_bool	all_args_correct;
    
	all_args_correct = ft_true;
    if (!arg_node)
        sort_and_print_var(mbox);
    while (arg_node)
    {
        equal_sign = NULL;
        equal_sign = ft_strchr(arg_node->content, '=');
        if (!equal_sign)
        {
            if (!validate_key(arg_node->content))
			{
                err_msg(mbox, NO_EXIT_STATUS, "nnnnnn", ERR_P, "export: `",
                    arg_node->content, SQ, CS, NO_VI);
				all_args_correct = ft_false;
			}
        }
        else
        {
            key = ft_substr(arg_node->content, 0,
                ft_strlen(arg_node->content) - ft_strlen(equal_sign));
            value = ft_substr(equal_sign, 1, ft_strlen(equal_sign)-1);
            if (validate_key(key))
                set_var_value(mbox, key, value);
            else
			{
                err_msg(mbox, NO_EXIT_STATUS, "nnnnnn", ERR_P, "export: `",
                    arg_node->content, SQ, CS, NO_VI);
				all_args_correct = ft_false;	
			}
            free_whatever("pp", key, value);
        }
        arg_node = arg_node->right;
    }
	if (all_args_correct)
		set_var_value(mbox, "?", EXIT_SUCCESS_STR);
	else
		set_var_value(mbox, "?", EXIT_FAILURE_STR);
}
